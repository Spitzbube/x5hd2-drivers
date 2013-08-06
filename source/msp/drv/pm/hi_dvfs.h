/*
 * hisilicon Management Routines
 *
 * Author: wang jian<vishwanath.bs@ti.com>
 *
 * Copyright (C) 2012 Hisilicon Instruments, Inc.
 * Wang Jian<stand.wang@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ARCH_ARM_MACH_HI_DVFS_H
#define __ARCH_ARM_MACH_HI_DVFS_H

int hi_device_scale(struct device *target_dev,unsigned long old_freq,unsigned long new_freq);
void do_avs(void);

#endif
