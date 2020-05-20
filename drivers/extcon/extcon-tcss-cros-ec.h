/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (C) 2018-2020 Intel Corporation */
/* Defines used by driver for the Intel Integrated Type-C Sub System Mux */

#define PMC_IPC_USBC_CMD_ID				0xA7

/* Connection request/response */
#define PMC_IPC_CONN_REQ_RES				0x0
#define PMC_IPC_CONN_REQ_WRITE_SIZE_BYTE		2

/* Disconnection request/response */
#define PMC_IPC_DIS_REQ_RES				0x1
#define PMC_IPC_DIS_REQ_WRITE_SIZE_BYTE			2

/* Safe mode request/response */
#define PMC_IPC_SFMODE_REQ_RES				0x2
#define PMC_IPC_SFMODE_REQ_WRITE_SIZE_BYTE		1

/* Alternate mode request/response */
#define PMC_IPC_ALTMODE_REQ_RES				0x3
#define PMC_IPC_ALT_REQ_WRITE_SIZE_BYTE			8

/* Hot Plug Detect request/response */
#define PMC_IPC_HPD_REQ_RES				0x4
#define PMC_IPC_HPD_REQ_WRITE_SIZE_BYTE			2

/*
 * TCSS request in hierarchy order
 * 1. Connect
 * 2. Disconnect
 * 3. Safe
 * 4. Alternate
 * 5. Display HPD
 */
#define TO_REQ(id)					(1 << (id))

/* PMC IPC request fields */
#define PMC_IPC_CONN_REQ_UFP				BIT(4)
#define PMC_IPC_CONN_REQ_ORI				GENMASK(6, 5)
#define PMC_IPC_CONN_REQ_DBG_ACC			BIT(7)

#define PMC_IPC_ALTMODE_REQ_MODE_DP			BIT(4)
#define PMC_IPC_ALTMODE_REQ_MODE_TBT_USB4		BIT(5)

/* Mode data [7:0] */
#define PMC_IPC_ALTMODE_REQ_MODE_DATA_CONN		BIT(1)
#define PMC_IPC_ALTMODE_REQ_MODE_DATA_CABLE		BIT(2)
#define PMC_IPC_ALTMODE_REQ_MODE_DATA_UFP		BIT(3)

/* Mode data [15:8] */
#define PMC_IPC_ALTMODE_REQ_MODE_HPD_HIGH		BIT(6)

/* Mode data [23:16] */
#define PMC_IPC_ALTMODE_REQ_MODE_TBT_TYPE		BIT(1)
#define PMC_IPC_ALTMODE_REQ_MODE_TBT_CABLE_TYPE		BIT(2)
#define PMC_IPC_ALTMODE_REQ_MODE_USB4_TBT_LINK_TR	BIT(4)
#define PMC_IPC_ALTMODE_REQ_MODE_USB4_CONN		BIT(7)

/* Mode data [23:16] */
#define PMC_IPC_ALTMODE_REQ_MODE_CABLE_SPEED_SHIFT	0x01

/* Mode data [31:24] */
#define PMC_IPC_ALTMODE_REQ_MODE_CABLE_GEN_SHIFT	0x04

/* Display HPD Request [15:8] */
#define PMC_IPC_DP_HPD_REQ_LVL				BIT(4)
#define PMC_IPC_DP_HPD_REQ_IRQ				BIT(5)

/* PMC IPC response fields */
#define PMC_IPC_CONN_RES_REQ_MASK			GENMASK(3, 0)
#define PMC_IPC_CONN_RES_USB3_PORT_MASK			GENMASK(7, 4)
#define PMC_IPC_CONN_RES_USB3_PORT_SHIFT		0x04
#define PMC_IPC_CONN_RES_USB2_PORT_MASK			GENMASK(11, 8)
#define PMC_IPC_CONN_RES_USB2_PORT_SHIFT		0x08

#define PMC_IPC_CONN_DIS_RES_STATUS_0			BIT(16)
#define PMC_IPC_CONN_DIS_RES_STATUS_1			BIT(17)
#define PMC_IPC_SAFE_ALT_HPD_RES_STATUS_0		BIT(8)
#define PMC_IPC_SAFE_ALT_HPD_RES_STATUS_1		BIT(9)

/* IOM PORT STATUS */
#define IOM_PORT_STATUS_ADDR				0xfbc10560
#define IOM_PORT_STATUS_LEN				16
#define IOM_PORT_STATUS_ACTIVITY_TYPE_MASK		GENMASK(9, 6)
#define IOM_PORT_STATUS_ACTIVITY_TYPE_SHIFT		0x06
#define IOM_PORT_STATUS_ACTIVITY_TYPE_USB		0x03
#define IOM_PORT_STATUS_ACTIVITY_TYPE_SAFE_MODE		0x04
#define IOM_PORT_STATUS_ACTIVITY_TYPE_DP		0x05
#define IOM_PORT_STATUS_ACTIVITY_TYPE_DP_MFD		0x06
#define IOM_PORT_STATUS_ACTIVITY_TYPE_TBT		0x07
#define IOM_PORT_STATUS_ACTIVITY_TYPE_ALT_MODE_USB	0x0c
#define IOM_PORT_STATUS_ACTIVITY_TYPE_ALT_MODE_TBT_USB	0x0d
#define IOM_PORT_STATUS_UFP				BIT(10)
#define IOM_PORT_STATUS_DHPD_HPD_STATUS_MASK		GENMASK(13, 12)
#define IOM_PORT_STATUS_DHPD_HPD_STATUS_SHIFT		0x0c
#define IOM_PORT_STATUS_DHPD_HPD_STATUS_ASSERT		0x01
#define IOM_PORT_STATUS_DHPD_HPD_SOURCE_TBT		BIT(14)
#define IOM_PORT_STATUS_CONNECTED			BIT(31)
#define IOM_MAX_PORTS					4
/* Register length in bytes */
#define IOM_REG_LEN					4

/*
 * TBT Cable Speed Support
 * 0x03: 10Gb/s and 20Gb/s only
 */
#define USBC_CABLE_USB32_GEN2				0x03

#define MUX_DATA_CONN_INFO(mux_data) \
		((mux_data)->polarity ? \
		 PMC_IPC_ALTMODE_REQ_MODE_DATA_CONN : 0) | \
		((mux_data)->active_cable ? \
		 PMC_IPC_ALTMODE_REQ_MODE_DATA_CABLE : 0) | \
		((mux_data)->ufp ? PMC_IPC_ALTMODE_REQ_MODE_DATA_UFP : 0)

/* reserved field of struct ec_response_locate_chip */
#define EC_USB2_PORT_MASK				0x0F
#define EC_USB3_PORT_SHIFT				4

/* Connection states */
enum pmc_ipc_conn_mode {
	PMC_IPC_DISCONNECT_MODE = 0,
	PMC_IPC_USB_MODE,
	PMC_IPC_SAFE_MODE,
	PMC_IPC_ALT_MODE,
	PMC_IPC_TOTAL_MODES,
};

/* TCSS Multiplexing data for a Type-C port */
struct tcss_mux {
	bool dp;
	bool usb;
	bool ufp;
	bool polarity;
	bool hpd_lvl;
	bool hpd_irq;
	bool dbg_acc;
	bool active_cable;
	bool tbt;
	bool usb4;
	bool tbt_type;
	bool optical_cable;
	bool tbt_usb4_link;

	u8 dp_mode;
	u8 tbt_usb4_cable_gen;
	u8 tbt_usb4_cable_speed;
};

/* Per Type-C Port data */
struct cros_ec_tcss_data {
	enum pmc_ipc_conn_mode conn_mode;
	u8 usb3_port;
	u8 usb2_port;
	struct tcss_mux mux_info;
};

/* Driver specific structure that holds info on all its dependencies */
struct cros_ec_tcss_info {
	u8 num_ports;
	struct work_struct bh_work;
	struct notifier_block notifier;
	struct device *dev;
	struct cros_ec_device *ec;
	struct cros_ec_tcss_data *tcss;
	struct intel_scu_ipc_dev *scu;
	/* Synchronize cable detection logic across callers */
	struct mutex lock;
	void __iomem *iom_port_status;
};

static const u8 tcss_requests[] = {
	TO_REQ(PMC_IPC_DIS_REQ_RES),
	TO_REQ(PMC_IPC_CONN_REQ_RES),
	TO_REQ(PMC_IPC_SFMODE_REQ_RES),
	TO_REQ(PMC_IPC_ALTMODE_REQ_RES),
	TO_REQ(PMC_IPC_HPD_REQ_RES),
};

/*
 * This look up table retrieves the request given previous mode and
 * the next mode.
 * [Previous mode] [next mode]
 *
 * TCSS state transition diagram
 * Ref: TCSS SAS document (b:147460168#comment71)
 *
 * USB-C Port modes: Open, USB, Safe, Alternate
 * TCSS Requests: Connect, Disconnect, Safe, Altenate, HPD
 */
static const u8 tcss_mode_states[][PMC_IPC_TOTAL_MODES] = {
	{ 0, TO_REQ(PMC_IPC_CONN_REQ_RES), TO_REQ(PMC_IPC_CONN_REQ_RES) |
	  TO_REQ(PMC_IPC_SFMODE_REQ_RES), TO_REQ(PMC_IPC_CONN_REQ_RES) |
	  TO_REQ(PMC_IPC_SFMODE_REQ_RES) | TO_REQ(PMC_IPC_ALTMODE_REQ_RES), },

	{ TO_REQ(PMC_IPC_DIS_REQ_RES), 0, TO_REQ(PMC_IPC_SFMODE_REQ_RES),
	  TO_REQ(PMC_IPC_SFMODE_REQ_RES) | TO_REQ(PMC_IPC_ALTMODE_REQ_RES), },

	{ TO_REQ(PMC_IPC_DIS_REQ_RES), TO_REQ(PMC_IPC_CONN_REQ_RES), 0,
	  TO_REQ(PMC_IPC_ALTMODE_REQ_RES), },

	{ TO_REQ(PMC_IPC_DIS_REQ_RES), TO_REQ(PMC_IPC_SFMODE_REQ_RES) |
	  TO_REQ(PMC_IPC_CONN_REQ_RES), TO_REQ(PMC_IPC_SFMODE_REQ_RES),
	  TO_REQ(PMC_IPC_ALTMODE_REQ_RES), },
};
