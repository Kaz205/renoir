// SPDX-License-Identifier: GPL-2.0
/*
 * Driver for the Intel Integrated Type-C Sub System Mux
 *
 * Copyright (C) 2018-2020 Intel Corporation
 *
 * Based on drivers/extcon/extcon-usbc-cros-ec.c
 *
 * This driver uses Intel PMC (Power Management Controller) IPC (Inter
 * Processor Communication) to configure the required muxing for the
 * Intel TCSS (Type-C Sub System)
 */

#include <linux/module.h>
#include <linux/platform_data/cros_ec_proto.h>
#include <linux/platform_data/cros_usbpd_notify.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/usb/typec_dp.h>

#include <asm/intel_scu_ipc.h>

#include "extcon-tcss-cros-ec.h"

/**
 * cros_ec_pd_command() - Send a command to the EC.
 * @info: pointer to struct cros_ec_tcss_info
 * @command: EC command
 * @version: EC command version
 * @outdata: EC command output data
 * @outsize: Size of outdata
 * @indata: EC command input data
 * @insize: Size of indata
 *
 * Return: 0 on success, error number on failure.
 */
static int cros_ec_pd_command(struct cros_ec_tcss_info *info,
			      unsigned int command, unsigned int version,
			      void *outdata, unsigned int outsize,
			      void *indata, unsigned int insize)
{
	struct cros_ec_command *msg;
	int ret;

	msg = kzalloc(sizeof(*msg) + max(outsize, insize), GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	msg->version = version;
	msg->command = command;
	msg->outsize = outsize;
	msg->insize = insize;

	memcpy(msg->data, outdata, outsize);

	ret = cros_ec_cmd_xfer_status(info->ec, msg);
	if (ret < 0)
		goto err;

	memcpy(indata, msg->data, insize);
err:
	kfree(msg);
	return ret;
}

/**
 * cros_ec_pd_get_port_info() - Get USB-C port's USB2 & USB3 num info.
 * @info: pointer to struct cros_ec_tcss_info
 * @port: USB-C port number
 *
 * Return: status of cros_ec_pd_command()
 */
static int cros_ec_pd_get_port_info(struct cros_ec_tcss_info *info,
				    u8 port)
{
	struct cros_ec_tcss_data *tcss_data = &info->tcss[port];
	struct ec_response_locate_chip resp;
	struct ec_params_locate_chip req;
	int ret;

	req.type = EC_CHIP_TYPE_TCPC;
	req.index = port;

	ret = cros_ec_pd_command(info, EC_CMD_LOCATE_CHIP, 0,
				 &req, sizeof(req), &resp, sizeof(resp));
	if (ret < 0)
		return ret;

	/* Assign USB2 & USB3 numbers */
	tcss_data->usb2_port = resp.reserved & EC_USB2_PORT_MASK;
	tcss_data->usb3_port = resp.reserved >> EC_USB3_PORT_SHIFT;

	return ret;
}

/**
 * cros_ec_pd_get_num_ports() - Get number of EC charge ports.
 * @info: pointer to struct cros_ec_tcss_info
 *
 * Return: status of cros_ec_pd_command()
 */
static int cros_ec_pd_get_num_ports(struct cros_ec_tcss_info *info)
{
	struct ec_response_usb_pd_ports resp;
	int ret;

	memset(&resp, 0, sizeof(resp));
	ret = cros_ec_pd_command(info, EC_CMD_USB_PD_PORTS, 0,
				 NULL, 0, &resp, sizeof(resp));
	if (ret < 0)
		return ret;

	info->num_ports = resp.num_ports;

	return ret;
}

/**
 * cros_ec_usb_get_pd_mux_state() - Get PD mux state for given port.
 * @info: pointer to struct cros_ec_tcss_info
 * @resp: pointer to struct ec_response_usb_pd_mux_info
 * @port: USB-C port number
 *
 * Return: status of cros_ec_pd_command()
 */
static int cros_ec_usb_get_pd_mux_state(struct cros_ec_tcss_info *info,
					struct ec_response_usb_pd_mux_info
					*resp, u8 port)
{
	struct ec_params_usb_pd_mux_info req;

	req.port = port;

	return cros_ec_pd_command(info, EC_CMD_USB_PD_MUX_INFO, 0,
				  &req, sizeof(req), resp, sizeof(*resp));
}

/**
 * cros_ec_usb_pd_control() - Get role info about possible PD device attached
 * to a given port.
 * @info: pointer to struct cros_ec_tcss_info
 * @resp: pointer to struct ec_response_usb_pd_control_v2
 * @port: USB-C port number
 *
 * Return: status of cros_ec_pd_command()
 */
static int cros_ec_usb_pd_control(struct cros_ec_tcss_info *info,
				  struct ec_response_usb_pd_control_v2
				  *resp, u8 port)
{
	struct ec_params_usb_pd_control pd_control;

	pd_control.port = port;
	pd_control.role = USB_PD_CTRL_ROLE_NO_CHANGE;
	pd_control.mux = USB_PD_CTRL_MUX_NO_CHANGE;
	pd_control.swap = USB_PD_CTRL_SWAP_NONE;

	return cros_ec_pd_command(info, EC_CMD_USB_PD_CONTROL, 2,
				  &pd_control, sizeof(pd_control), resp,
				  sizeof(*resp));
}

static const char *cros_ec_conn_mode_to_string(const struct cros_ec_tcss_data
					       *port_data)
{
	switch (port_data->conn_mode) {
	case PMC_IPC_SAFE_MODE:
		return "Safe Mode";

	case PMC_IPC_ALT_MODE:
		if (port_data->mux_info.tbt)
			return "TBT Alternate mode";
		else if (port_data->mux_info.usb4)
			return "USB4 Mode";
		else
			return "DP Alternate mode";

	case PMC_IPC_USB_MODE:
		return "USB mode";

	case PMC_IPC_DISCONNECT_MODE:
		return "Disconnect mode";

	default:
		return "Unknown mode";
	}
}

static int cros_ec_tcss_get_current_state(struct cros_ec_tcss_info *info,
					  struct cros_ec_tcss_data *port_data,
					  u8 port)
{
	struct ec_response_usb_pd_control_v2 pd_resp;
	struct ec_response_usb_pd_mux_info mux_resp;
	struct tcss_mux *mux_info;
	int ret;

	if (!info || !port_data)
		return -EIO;

	mux_info = &port_data->mux_info;
	if (!mux_info)
		return -EIO;

	ret = cros_ec_usb_get_pd_mux_state(info, &mux_resp, port);
	if (ret < 0) {
		dev_err(info->dev, "failed getting mux state = %d\n", ret);
		return ret;
	}

	ret = cros_ec_usb_pd_control(info, &pd_resp, port);
	if (ret < 0) {
		dev_err(info->dev, "failed getting role err = %d\n", ret);
		return ret;
	}

	mux_info->dp_mode = pd_resp.dp_mode;
	mux_info->tbt_usb4_cable_speed = pd_resp.cable_speed;
	mux_info->tbt_usb4_cable_gen = pd_resp.cable_gen;

	mux_info->ufp = !(pd_resp.role & PD_CTRL_RESP_ROLE_DATA);
	mux_info->dbg_acc = (pd_resp.cc_state == PD_CC_UFP_DEBUG_ACC ||
			     pd_resp.cc_state == PD_CC_DFP_DEBUG_ACC);

	mux_info->active_cable = !!(pd_resp.control_flags &
				    USB_PD_CTRL_ACTIVE_CABLE);

	mux_info->optical_cable = !!(pd_resp.control_flags &
				     USB_PD_CTRL_OPTICAL_CABLE);

	mux_info->tbt_type = !!(pd_resp.control_flags &
				USB_PD_CTRL_TBT_LEGACY_ADAPTER);

	mux_info->tbt_usb4_link = !!(pd_resp.control_flags &
				     USB_PD_CTRL_ACTIVE_LINK_UNIDIR);

	mux_info->dp = !!(mux_resp.flags & USB_PD_MUX_DP_ENABLED);

	mux_info->usb = !!(mux_resp.flags & USB_PD_MUX_USB_ENABLED);

	mux_info->polarity = !!(mux_resp.flags & USB_PD_MUX_POLARITY_INVERTED);

	mux_info->hpd_lvl = !!(mux_resp.flags & USB_PD_MUX_HPD_LVL);

	mux_info->hpd_irq = !!(mux_resp.flags & USB_PD_MUX_HPD_IRQ);

	mux_info->tbt = !!(mux_resp.flags & USB_PD_MUX_TBT_COMPAT_ENABLED);

	mux_info->usb4 = !!(mux_resp.flags & USB_PD_MUX_USB4_ENABLED);

	if (mux_resp.flags & USB_PD_MUX_SAFE_MODE)
		port_data->conn_mode = PMC_IPC_SAFE_MODE;
	else if (mux_info->dp || mux_info->tbt || mux_info->usb4)
		port_data->conn_mode = PMC_IPC_ALT_MODE;
	else if (mux_info->usb)
		port_data->conn_mode = PMC_IPC_USB_MODE;
	else
		port_data->conn_mode = PMC_IPC_DISCONNECT_MODE;

	dev_dbg(info->dev, " Port=%d, Connection mode = %s\n", port,
		cros_ec_conn_mode_to_string(port_data));

	return 0;
}

/**
 * cros_ec_tcss_get_next_state_req() - Get the request for the next state.
 * @port_data: pointer to struct cros_ec_tcss_data (current state)
 * @prev_port_data: pointer to struct cros_ec_tcss_data (previous state)
 *
 * Return: Request for next state, 0 if nothing needs to be done
 */
static
u8 cros_ec_tcss_get_next_state_req(struct cros_ec_tcss_data *port_data,
				   struct cros_ec_tcss_data *prev_port_data)
{
	u8 ret =
	    tcss_mode_states[prev_port_data->conn_mode][port_data->conn_mode];

	/* Handle HPD in Alternate Mode */
	if (ret & TO_REQ(PMC_IPC_ALTMODE_REQ_RES)) {
		if (prev_port_data->conn_mode == PMC_IPC_ALT_MODE) {
			/* Alternate mode HPD/IRQ changed */
			if (port_data->mux_info.hpd_irq ||
			    port_data->mux_info.hpd_lvl !=
			    prev_port_data->mux_info.hpd_lvl)
				ret = TO_REQ(PMC_IPC_HPD_REQ_RES);
			/* Nothing to change */
			else
				ret = 0;
		} else {
			/* Alternate mode has HPD/IRQ */
			if (port_data->mux_info.hpd_irq ||
			    port_data->mux_info.hpd_lvl)
				ret |= TO_REQ(PMC_IPC_HPD_REQ_RES);
		}
	}
	return ret;
}

static void cros_ec_tcss_altmode_req(struct tcss_mux *mux_data, u8 *tcss_req)
{
	if (!mux_data || !tcss_req)
		return;

	tcss_req[4] = MUX_DATA_CONN_INFO(mux_data);

	if (mux_data->dp) {
		tcss_req[1] |= PMC_IPC_ALTMODE_REQ_MODE_DP;

		tcss_req[5] = ffs(mux_data->dp_mode);

		tcss_req[5] |= mux_data->hpd_lvl ?
		       PMC_IPC_ALTMODE_REQ_MODE_HPD_HIGH : 0;

		return;
	}

	/* USB4 or TBT */
	tcss_req[1] |= PMC_IPC_ALTMODE_REQ_MODE_TBT_USB4;

	tcss_req[6] = (mux_data->tbt_type ?
		       PMC_IPC_ALTMODE_REQ_MODE_TBT_TYPE : 0) |
		      (mux_data->optical_cable ?
		       PMC_IPC_ALTMODE_REQ_MODE_TBT_CABLE_TYPE : 0) |
		      (mux_data->tbt_usb4_link ?
		       PMC_IPC_ALTMODE_REQ_MODE_USB4_TBT_LINK_TR : 0) |
		      (mux_data->usb4 ?
		       PMC_IPC_ALTMODE_REQ_MODE_USB4_CONN : 0);

	if (mux_data->tbt_usb4_cable_speed <= USBC_CABLE_USB32_GEN2)
		tcss_req[7] = (mux_data->tbt_usb4_cable_speed <<
			       PMC_IPC_ALTMODE_REQ_MODE_CABLE_SPEED_SHIFT);

	tcss_req[7] |= (mux_data->tbt_usb4_cable_gen <<
			PMC_IPC_ALTMODE_REQ_MODE_CABLE_GEN_SHIFT);
}

static int cros_ec_tcss_req(struct cros_ec_tcss_info *info, int req_type,
			    u8 port, struct tcss_mux *mux_data)
{
	struct cros_ec_tcss_data *tcss_info = &info->tcss[port];
	bool retry_pmc_cmd = true, pmc_cmd_sts_0, pmc_cmd_sts_1;
	struct device *dev = info->dev;
	u32 write_size, tcss_res = 0;
	u8 tcss_req[8] = { 0 };
	int ret;

	tcss_req[0] = req_type | tcss_info->usb3_port << EC_USB3_PORT_SHIFT;

	switch (req_type) {
	case PMC_IPC_CONN_REQ_RES:
		tcss_req[1] = tcss_info->usb2_port |
			      (mux_data->ufp ? PMC_IPC_CONN_REQ_UFP : 0) |
			      (mux_data->polarity ? PMC_IPC_CONN_REQ_ORI : 0) |
			      (mux_data->dbg_acc ?
			       PMC_IPC_CONN_REQ_DBG_ACC : 0);
		write_size = PMC_IPC_CONN_REQ_WRITE_SIZE_BYTE;
	break;

	case PMC_IPC_DIS_REQ_RES:
		tcss_req[1] = tcss_info->usb2_port;
		write_size = PMC_IPC_DIS_REQ_WRITE_SIZE_BYTE;
		break;

	case PMC_IPC_SFMODE_REQ_RES:
		write_size = PMC_IPC_SFMODE_REQ_WRITE_SIZE_BYTE;
		break;

	case PMC_IPC_ALTMODE_REQ_RES:
		cros_ec_tcss_altmode_req(mux_data, tcss_req);
		write_size = PMC_IPC_ALT_REQ_WRITE_SIZE_BYTE;
		break;

	case PMC_IPC_HPD_REQ_RES:
		tcss_req[1] = (mux_data->hpd_lvl ? PMC_IPC_DP_HPD_REQ_LVL : 0) |
			      (mux_data->hpd_irq ? PMC_IPC_DP_HPD_REQ_IRQ : 0);
		write_size = PMC_IPC_HPD_REQ_WRITE_SIZE_BYTE;
		break;

	default:
		dev_err(dev, "Invalid req type to PMC = %d", req_type);
		goto err;
	}

retry_pmc_ipc_cmd:
	tcss_res = 0;
	ret = intel_scu_ipc_dev_command(info->scu, PMC_IPC_USBC_CMD_ID, 0,
					tcss_req, write_size, &tcss_res,
					sizeof(tcss_res));
	if (ret) {
		dev_err(dev, "IPC to PMC failed with error %d\n", ret);
		goto err;
	}

	if ((tcss_res & PMC_IPC_CONN_RES_REQ_MASK) != req_type)
		goto err;
	if ((tcss_res & PMC_IPC_CONN_RES_USB3_PORT_MASK) !=
	    (tcss_info->usb3_port << PMC_IPC_CONN_RES_USB3_PORT_SHIFT))
		goto err;

	switch (req_type) {
	case PMC_IPC_CONN_REQ_RES:
	case PMC_IPC_DIS_REQ_RES:
		if ((tcss_res & PMC_IPC_CONN_RES_USB2_PORT_MASK) !=
		    (tcss_info->usb2_port << PMC_IPC_CONN_RES_USB2_PORT_SHIFT))
			goto err;
		pmc_cmd_sts_0 = !!(tcss_res & PMC_IPC_CONN_DIS_RES_STATUS_0);
		pmc_cmd_sts_1 = !!(tcss_res & PMC_IPC_CONN_DIS_RES_STATUS_1);
		break;
	case PMC_IPC_SFMODE_REQ_RES:
	case PMC_IPC_ALTMODE_REQ_RES:
	case PMC_IPC_HPD_REQ_RES:
		pmc_cmd_sts_0 =
			!!(tcss_res & PMC_IPC_SAFE_ALT_HPD_RES_STATUS_0);
		pmc_cmd_sts_1 =
			!!(tcss_res & PMC_IPC_SAFE_ALT_HPD_RES_STATUS_1);
		break;
	default:
		dev_err(dev, "Invalid req type to PMC = %d", req_type);
		goto err;
	}

	if (!pmc_cmd_sts_0)
		return 0;

	if (!pmc_cmd_sts_1 && retry_pmc_cmd) {
		retry_pmc_cmd = false;
		dev_warn(dev, "PMC IPC CMD retry: port=%d, req=%d\n",
				port, req_type);
		goto retry_pmc_ipc_cmd;
	}

err:
	dev_err(dev, "PMC TCSS failed port=%d, req=%d, tcss_res=0x%x\n",
		port, req_type, tcss_res);
	return -EIO;
}

static int cros_ec_tcss_detect_cable(struct cros_ec_tcss_info *info,
				     bool force, u8 port)
{
	struct cros_ec_tcss_data *tcss_info;
	struct cros_ec_tcss_data port_data;
	u8 next_seq;
	int ret, i;

	if (!info)
		return -EIO;

	tcss_info = &info->tcss[port];
	ret = cros_ec_tcss_get_current_state(info, &port_data, port);
	if (ret < 0)
		return ret;

	next_seq = cros_ec_tcss_get_next_state_req(&port_data, tcss_info);
	if (!next_seq)
		return 0;

	dev_dbg(info->dev, "p=%d,ufp=%d,dp=%d,usb=%d,pol=%d\n",
		port, port_data.mux_info.ufp, port_data.mux_info.dp,
		port_data.mux_info.usb, port_data.mux_info.polarity);

	dev_dbg(info->dev, "hpd=%d,irq=%d,mode=%d,con=%d\n",
		port_data.mux_info.hpd_lvl, port_data.mux_info.hpd_irq,
		port_data.mux_info.dp_mode, port_data.conn_mode);

	dev_info(info->dev,
		 "tbt=%d,usb4=%d tbt_type=%d, optical_cable=%d, tbt_usb4_link=%d\n",
		 port_data.mux_info.tbt, port_data.mux_info.usb4,
		 port_data.mux_info.tbt_type, port_data.mux_info.optical_cable,
		 port_data.mux_info.tbt_usb4_link);

	dev_info(info->dev, "tbt_usb4_cable_speed=%d, tbt_usb4_cable_gen=%d\n",
		 port_data.mux_info.tbt_usb4_cable_speed,
		 port_data.mux_info.tbt_usb4_cable_gen);

	for (i = 0; i < ARRAY_SIZE(tcss_requests); i++) {
		if (next_seq & tcss_requests[i]) {
			ret = cros_ec_tcss_req(info,
					       (ffs(tcss_requests[i]) - 1),
					       port, &port_data.mux_info);
			if (ret)
				break;
		}
	}

	if (ret) {
		dev_err(info->dev, "Error port=%d, error=%d\n", port, ret);
	} else {
		port_data.mux_info.hpd_irq = 0;
		tcss_info->mux_info = port_data.mux_info;
		tcss_info->conn_mode = port_data.conn_mode;
	}

	return ret;
}

static void cros_ec_tcss_bh_work(struct work_struct *work)
{
	struct cros_ec_tcss_info *info =
		container_of(work, struct cros_ec_tcss_info, bh_work);
	u8 i;

	mutex_lock(&info->lock);
	for (i = 0; i < info->num_ports; i++) {
		if (cros_ec_tcss_detect_cable(info, false, i) >= 0)
			continue;
		dev_err(info->dev, "Port %d, Error detecting cable\n", i);
		break;
	}
	mutex_unlock(&info->lock);
}

static int cros_ec_tcss_event(struct notifier_block *nb,
			      unsigned long queued_during_suspend,
			      void *_notify)
{
	struct cros_ec_tcss_info *info =
		container_of(nb, struct cros_ec_tcss_info, notifier);

	if (info)
		schedule_work(&info->bh_work);

	return NOTIFY_DONE;
}

static int cros_ec_tcss_remove(struct platform_device *pdev)
{
	struct cros_ec_tcss_info *info = platform_get_drvdata(pdev);

	cros_usbpd_unregister_notify(&info->notifier);
	cancel_work_sync(&info->bh_work);
	mutex_destroy(&info->lock);

	return 0;
}

static int cros_ec_tcss_probe(struct platform_device *pdev)
{
	struct cros_ec_tcss_info *info;
	struct cros_ec_device *ec;
	struct device *dev;
	int ret;
	u8 i;

	if (!pdev || !pdev->dev.parent)
		return -ENODEV;

	ec = dev_get_drvdata(pdev->dev.parent);
	dev = &pdev->dev;

	if (!ec || !dev)
		return -ENODEV;

	info = devm_kzalloc(dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->ec = ec;
	info->dev = dev;

	info->scu = devm_intel_scu_ipc_dev_get(dev);
	if (!info->scu)
		return -EPROBE_DEFER;

	ret = cros_ec_pd_get_num_ports(info);
	if (ret < 0) {
		dev_err(dev, "failed getting number of ports! ret = %d\n", ret);
		return -ENODEV;
	}

	info->tcss = devm_kzalloc(dev, sizeof(*info->tcss) * info->num_ports,
				  GFP_KERNEL);
	if (!info->tcss)
		return -ENOMEM;

	platform_set_drvdata(pdev, info);

	mutex_init(&info->lock);
	INIT_WORK(&info->bh_work, cros_ec_tcss_bh_work);

	/* Get Port detection events from the EC */
	info->notifier.notifier_call = cros_ec_tcss_event;
	ret = cros_usbpd_register_notify(&info->notifier);
	if (ret < 0) {
		dev_err(dev, "failed to register notifier\n");
		goto destroy_mutex;
	}

	mutex_lock(&info->lock);
	/* Perform initial detection */
	for (i = 0; i < info->num_ports; i++) {
		ret = cros_ec_pd_get_port_info(info, i);
		if (ret < 0) {
			dev_err(dev, "failed getting USB port info! ret = %d\n",
				ret);
			goto remove_tcss;
		}

		ret = cros_ec_tcss_detect_cable(info, true, i);
		if (ret < 0) {
			dev_err(dev, "failed to detect initial cable state\n");
			goto remove_tcss;
		}
	}
	mutex_unlock(&info->lock);

return 0;

remove_tcss:
	mutex_unlock(&info->lock);
	cros_usbpd_unregister_notify(&info->notifier);
	cancel_work_sync(&info->bh_work);
destroy_mutex:
	mutex_destroy(&info->lock);

	return ret;
}

#ifdef CONFIG_PM_SLEEP
static int cros_ec_tcss_resume(struct device *dev)
{
	struct cros_ec_tcss_info *info = dev_get_drvdata(dev);
	int ret;
	u8 i;

	mutex_lock(&info->lock);
	for (i = 0; i < info->num_ports; i++) {
		ret = cros_ec_tcss_detect_cable(info, false, i);
		if (ret < 0) {
			dev_err(dev, "cable detection failed on resume\n");
			mutex_unlock(&info->lock);
			return ret;
		}
	}
	mutex_unlock(&info->lock);

	return 0;
}

static const struct dev_pm_ops tcss_cros_ec_dev_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(NULL, cros_ec_tcss_resume)
};

#define DEV_PM_OPS     (&tcss_cros_ec_dev_pm_ops)
#else
#define DEV_PM_OPS     NULL
#endif /* CONFIG_PM_SLEEP */

static struct platform_driver tcss_cros_ec_driver = {
	.driver = {
		   .name = "extcon-tcss-cros-ec",
		   .pm = DEV_PM_OPS,
	},
	.remove = cros_ec_tcss_remove,
	.probe = cros_ec_tcss_probe,
};

module_platform_driver(tcss_cros_ec_driver);

MODULE_DESCRIPTION("ChromeOS Embedded Controller Intel TCSS driver");
MODULE_AUTHOR("Vijay P Hiremath <vijay.p.hiremath@intel.com>");
MODULE_AUTHOR("Divya Sasidharan <divya.s.sasidharan@intel.com>");
MODULE_AUTHOR("Utkarsh Patel <utkarsh.h.patel@intel.com>");
MODULE_LICENSE("GPL v2");
