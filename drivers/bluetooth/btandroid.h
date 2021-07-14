/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 *  Bluetooth support for Android specifications
 *
 *  Copyright (C) 2021 Google Corporation
 */

#include <net/bluetooth/hci_core.h>

#if IS_ENABLED(CONFIG_BT_FEATURE_QUALITY_REPORT)

int btandroid_set_quality_report(struct hci_dev *hdev, bool enable);

#else

static inline int btandroid_set_quality_report(struct hci_dev *hdev,
					       bool enable)
{
	return -EOPNOTSUPP;
}

#endif
