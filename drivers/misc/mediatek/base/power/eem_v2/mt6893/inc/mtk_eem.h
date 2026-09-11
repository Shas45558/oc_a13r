/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 MediaTek Inc.
 */

#ifndef _MTK_EEM_
#define _MTK_EEM_

#include <linux/kernel.h>
#include <mt-plat/sync_write.h>
#include <mt-plat/mboot_params.h>
#include "mtk_eem_config.h"

#define EN_EEM (1) /* enable/disable EEM (SW) */

/* have 5 banks */
enum eem_ctrl_id {
	EEM_CTRL_L,
	EEM_CTRL_BL,
	EEM_CTRL_B,
	EEM_CTRL_CCI,

	NR_EEM_CTRL,
};

enum eem_det_id {
	EEM_DET_L	=	EEM_CTRL_L,
	EEM_DET_BL	=	EEM_CTRL_BL,
	EEM_DET_B	=	EEM_CTRL_B,
	EEM_DET_CCI	=	EEM_CTRL_CCI,

	NR_EEM_DET,
};

enum mt_eem_cpu_id {
	MT_EEM_CPU_LL,
	MT_EEM_CPU_L,
	MT_EEM_CPU_B,
	MT_EEM_CPU_CCI,

	NR_MT_EEM_CPU,
};

enum mt_eem_add_extra_mode {
	NO_EXTRA,
	ADD_EXTRA,
	UNDEF_EXTRA,
};

/* internal use */
/* EEM detector is disabled by who */
enum {
	BY_PROCFS	= BIT(0),
	BY_INIT_ERROR	= BIT(1),
	BY_MON_ERROR	= BIT(2),
};

enum eem_phase {
	EEM_PHASE_INIT020,
	EEM_PHASE_INIT021,
	EEM_PHASE_INIT022,
#if SUPPORT_BL_ULV
	EEM_PHASE_INIT023,
#endif
	EEM_PHASE_MON,

	NR_EEM_PHASE,
};

enum eem_features {
	FEA_INIT020	= BIT(EEM_PHASE_INIT020),
	FEA_INIT021	= BIT(EEM_PHASE_INIT021),
	FEA_INIT022	= BIT(EEM_PHASE_INIT022),
#if SUPPORT_BL_ULV
	FEA_INIT023	= BIT(EEM_PHASE_INIT023),
#endif
	FEA_MON		= BIT(EEM_PHASE_MON),
};

enum {
	EEM_VOLT_NONE	= 0,
	EEM_VOLT_UPDATE  = BIT(0),
	EEM_VOLT_RESTORE = BIT(1),
};

enum {
	EEM_NORMAL_T	= 0,
	EEM_LOW_T,
	EEM_MID_T,
	EEM_HIGH_T
};

#if ENABLE_LOO
enum eem_loo_role {
	NO_LOO_BANK	=	0,
	LOW_BANK	=	1,
	HIGH_BANK	=	2,

	NR_EEM_LOO_BANK,
};
#endif

extern u32 get_devinfo_with_index(u32 index);
extern unsigned int eem_corn_flag;
extern const unsigned int reg_dump_addr_off[DUMP_LEN];

#ifdef CONFIG_MTK_RAM_CONSOLE
#define CONFIG_EEM_AEE_RR_REC 1
#endif

#ifdef CONFIG_EEM_AEE_RR_REC
enum eem_state {
	EEM_CPU_2_LITTLE_IS_SET_VOLT = 0,	/* 2L */
	EEM_CPU_LITTLE_IS_SET_VOLT = 1,		/* BL */
	EEM_CPU_B_IS_SET_VOLT = 2,			/* B */
	EEM_CPU_CCI_IS_SET_VOLT = 3,		/* CCI */
};
#endif

/* EEM Extern Function */
extern int mt_eem_status(enum eem_det_id id);
extern unsigned int get_efuse_status(void);
extern unsigned int mt_eem_is_enabled(void);
#endif
