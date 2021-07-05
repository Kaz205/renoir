// SPDX-License-Identifier: ISC

#include "mt7921.h"
#include "mcu.h"

enum mt7921_testmode_attr {
	MT7921_TM_ATTR_UNSPEC,
	MT7921_TM_ATTR_SET,
	MT7921_TM_ATTR_QUERY,
	MT7921_TM_ATTR_RSP,

	/* keep last */
	NUM_MT7921_TM_ATTRS,
	MT7921_TM_ATTR_MAX = NUM_MT7921_TM_ATTRS - 1,
};

struct mt7921_tm_cmd {
	u8 action;
	u32 param0;
	u32 param1;
};

struct mt7921_tm_evt {
	u32 param0;
	u32 param1;
};

static const struct nla_policy mt7921_tm_policy[NUM_MT7921_TM_ATTRS] = {
	[MT7921_TM_ATTR_SET] = NLA_POLICY_EXACT_LEN(sizeof(struct mt7921_tm_cmd)),
	[MT7921_TM_ATTR_QUERY] = NLA_POLICY_EXACT_LEN(sizeof(struct mt7921_tm_cmd)),
};

static int
mt7921_tm_set(struct mt7921_dev *dev, struct mt7921_tm_cmd *req)
{
	struct mt7921_rftest_cmd cmd = {
		.action = req->action,
		.param0 = cpu_to_le32(req->param0),
		.param1 = cpu_to_le32(req->param1),
	};
	bool to_testmode = false, to_normal = false;
	struct mt76_connac_pm *pm = &dev->pm;
	struct mt76_phy *phy = &dev->mphy;
	int ret = -ENOTCONN;

	mutex_lock(&dev->mt76.mutex);

	if (req->action == TM_SWITCH_MODE) {
		if (req->param0 != MT7921_TM_NORMAL)
			to_testmode = true;
		else
			to_normal = true;
	}

	if (to_testmode) {
		/* Make sure testmode running on full power mode */
		pm->enable = false;
		cancel_delayed_work_sync(&pm->ps_work);
		cancel_work_sync(&pm->wake_work);
		__mt7921_mcu_drv_pmctrl(dev);

		mt76_wr(dev, MT_WF_RFCR(0), dev->mt76.rxfilter);
		phy->test.state = MT76_TM_STATE_ON;
	}

	if (!mt76_testmode_enabled(phy))
		goto out;

	ret = mt76_mcu_send_msg(&dev->mt76, MCU_CMD_TEST_CTRL, &cmd,
				sizeof(cmd), false);

	if (to_normal) {
		/* Switch back to the normal world */
		phy->test.state = MT76_TM_STATE_OFF;
		pm->enable = true;
	}
out:
	mutex_unlock(&dev->mt76.mutex);

	return ret;
}

static int
mt7921_tm_query(struct mt7921_dev *dev, struct mt7921_tm_cmd *req,
		struct mt7921_tm_evt *resp)
{
	struct mt7921_rftest_cmd cmd = {
		.action = req->action,
		.param0 = cpu_to_le32(req->param0),
		.param1 = cpu_to_le32(req->param1),
	};
	struct mt7921_rftest_evt *evt;
	struct sk_buff *skb;
	int ret;

	mutex_lock(&dev->mt76.mutex);

	ret = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_CMD_TEST_CTRL,
					&cmd, sizeof(cmd), true, &skb);
	mutex_unlock(&dev->mt76.mutex);

	if (ret)
		goto out;

	evt = (struct mt7921_rftest_evt *)(skb->data);
	resp->param0 = le32_to_cpu(evt->param0);
	resp->param1 = le32_to_cpu(evt->param1);
out:
	dev_kfree_skb(skb);

	return ret;
}

int mt7921_testmode_cmd(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			void *data, int len)
{
	struct nlattr *tb[NUM_MT7921_TM_ATTRS];
	struct mt76_phy *mphy = hw->priv;
	struct mt7921_phy *phy = mphy->priv;
	struct mt7921_dev *dev = phy->dev;
	int err;

	if (!test_bit(MT76_STATE_RUNNING, &mphy->state) ||
	    !(hw->conf.flags & IEEE80211_CONF_MONITOR))
		return -ENOTCONN;

	err = nla_parse_deprecated(tb, MT7921_TM_ATTR_MAX, data, len,
				   mt7921_tm_policy, NULL);
	if (err)
		return err;

	err = -EINVAL;
	if (tb[MT7921_TM_ATTR_SET])
		err = mt7921_tm_set(dev, nla_data(tb[MT7921_TM_ATTR_SET]));

	return err;
}

int mt7921_testmode_dump(struct ieee80211_hw *hw, struct sk_buff *msg,
			 struct netlink_callback *cb, void *data, int len)
{
	struct nlattr *tb[NUM_MT7921_TM_ATTRS];
	struct mt76_phy *mphy = hw->priv;
	struct mt7921_phy *phy = mphy->priv;
	struct mt7921_dev *dev = phy->dev;
	struct mt7921_tm_evt resp;
	int err;

	if (!test_bit(MT76_STATE_RUNNING, &mphy->state) ||
	    !(hw->conf.flags & IEEE80211_CONF_MONITOR) ||
	    !mt76_testmode_enabled(mphy))
		return -ENOTCONN;

	if (cb->args[2]++ > 0)
		return -ENOENT;

	err = nla_parse_deprecated(tb, MT7921_TM_ATTR_MAX, data, len,
				   mt7921_tm_policy, NULL);
	if (err)
		return err;

	err = -EINVAL;
	if (tb[MT7921_TM_ATTR_QUERY]) {
		err = mt7921_tm_query(dev, nla_data(tb[MT7921_TM_ATTR_QUERY]), &resp);
		if (err)
			goto out;

		err = nla_put(msg, MT7921_TM_ATTR_RSP, sizeof(resp), &resp);
	}
out:
	return err;
}
