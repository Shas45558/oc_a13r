/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
*/

#ifndef _MTK_EEM_
#define _MTK_EEM_

#ifdef __KERNEL__
#include <linux/kernel.h>
#include <mt-plat/sync_write.h>
#include <mt-plat/mboot_params.h>
#endif

#define EN_EEM (1) /* enable/disable EEM (SW) */

/* have 3 banks at maximum */
enum eem_ctrl_id {
	EEM_CTRL_2L = 0,
#ifndef CONFIG_MACH_MT6739
	EEM_CTRL_L,
	EEM_CTRL_CCI,
#endif
	EEM_CTRL_GPU,
	EEM_CTRL_SOC,
	NR_EEM_CTRL,
};

enum eem_det_id {
	EEM_DET_2L	=	EEM_CTRL_2L,
#ifndef CONFIG_MACH_MT6739
	EEM_DET_L	=	EEM_CTRL_L,
	EEM_DET_CCI	=	EEM_CTRL_CCI,
#endif
	EEM_DET_GPU	=	EEM_CTRL_GPU,
	EEM_DET_SOC	=	EEM_CTRL_SOC,
	NR_EEM_DET,
};


/* internal use */
/* EEM detector is disabled by who */
enum {
	BY_PROCFS	= BIT(0),
	BY_INIT_ERROR	= BIT(1),
	BY_MON_ERROR	= BIT(2),
	BY_PROCFS_INIT2 = BIT(3),
};

enum eem_phase {
	EEM_PHASE_INIT01,
	EEM_PHASE_INIT02,
	EEM_PHASE_MON,

	NR_EEM_PHASE,
};

enum eem_features {
	FEA_INIT01	= BIT(EEM_PHASE_INIT01),
	FEA_INIT02	= BIT(EEM_PHASE_INIT02),
	FEA_MON		= BIT(EEM_PHASE_MON),
};

enum {
	EEM_VOLT_NONE	= 0,
	EEM_VOLT_UPDATE  = BIT(0),
	EEM_VOLT_RESTORE = BIT(1),
};

/* Global variable for SW EFUSE*/
/* TODO: FIXME #include "devinfo.h" */
extern u32 get_devinfo_with_index(u32 index);
extern const unsigned int reg_dump_addr_off[101];

#ifdef CONFIG_MTK_RAM_CONSOLE
	#define CONFIG_EEM_AEE_RR_REC 1
#endif

#ifdef CONFIG_EEM_AEE_RR_REC
enum eem_state {
	EEM_CPU_2_LITTLE_IS_SET_VOLT = 0,	/* 2L */
	EEM_CPU_LITTLE_IS_SET_VOLT,		/* L */
	EEM_CPU_CCI_IS_SET_VOLT,		/* CCI */
	EEM_GPU_IS_SET_VOLT,			/* G */
};
#endif

extern int spm_mtcmos_ctrl_mfg1(int state);
extern int spm_mtcmos_ctrl_mfg2(int state);

/* EEM Extern Function */
/* extern void mt_ptp_lock(unsigned long *flags); */
/* extern void mt_ptp_unlock(unsigned long *flags); */
extern int mt_eem_status(enum eem_det_id id);
extern unsigned int get_vcore_ptp_volt(unsigned int uv);
/* extern void eem_set_pi_offset(enum eem_ctrl_id id, int step); */
extern void eem_set_pi_efuse(enum eem_det_id id, unsigned int pi_efuse);
extern unsigned int get_efuse_status(void);
extern unsigned int mt_eem_is_enabled(void);
extern unsigned int mt_eem_vcorefs_set_volt(void);
extern unsigned char mt_eem_get_turbo(void);

#if defined(__MTK_SLT_)
/* extern int mt_ptp_idle_can_enter(void); */
extern unsigned int ptp_init01_ptp(int id);
extern int ptp_isr(void);
#endif

#endif
