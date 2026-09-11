/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2015 MediaTek Inc.
 */

#if !defined(__AEE_H__)
#define __AEE_H__

#include <linux/kernel.h>
#include <linux/param.h>
#include <linux/ratelimit.h>
#include <linux/sched.h>
#include <linux/bug.h>
#include <linux/printk.h>

#define AEE_MODULE_NAME_LENGTH 64
#define AEE_PROCESS_NAME_LENGTH 256
#define AEE_BACKTRACE_LENGTH 3072
#define MODULES_INFO_BUF_SIZE SZ_16K


enum AEE_REBOOT_MODE {
    AEE_REBOOT_MODE_NORMAL = 0,
    AEE_REBOOT_MODE_KERNEL_OOPS,
    AEE_REBOOT_MODE_KERNEL_PANIC,
    AEE_REBOOT_MODE_NESTED_EXCEPTION,
    AEE_REBOOT_MODE_WDT,
    AEE_REBOOT_MODE_MANUAL_KDUMP,
    AEE_REBOOT_MODE_MRDUMP_KEY,
    AEE_REBOOT_MODE_GZ_KE,
    AEE_REBOOT_MODE_GZ_WDT,
    AEE_REBOOT_MODE_HANG_DETECT,
};

/* DB dump option bits, set relative bit to 1 to include related file in db */
#define DB_OPT_DEFAULT				(0)
#define DB_OPT_FTRACE				(1<<0)
#define DB_OPT_PRINTK_TOO_MUCH			(1<<1)
#define DB_OPT_NE_JBT_TRACES			(1<<2)
#define DB_OPT_SWT_JBT_TRACES			(1<<3)
#define DB_OPT_VM_TRACES			(1<<4)
#define DB_OPT_DUMPSYS_ACTIVITY			(1<<5)
#define DB_OPT_DUMPSYS_WINDOW			(1<<6)
#define DB_OPT_DUMPSYS_GFXINFO			(1<<7)
#define DB_OPT_DUMPSYS_SURFACEFLINGER		(1<<8)
#define DB_OPT_DISPLAY_HANG_DUMP		(1<<9)
#define DB_OPT_LOW_MEMORY_KILLER		(1<<10)
#define DB_OPT_PROC_MEM				(1<<11)
#define DB_OPT_FS_IO_LOG			(1<<12)
#define DB_OPT_PROCESS_COREDUMP			(1<<13)
#define DB_OPT_VM_HPROF				(1<<14)
#define DB_OPT_PROCMEM				(1<<15)
#define DB_OPT_DUMPSYS_INPUT			(1<<16)
#define DB_OPT_MMPROFILE_BUFFER			(1<<17)
#define DB_OPT_BINDER_INFO			(1<<18)
#define DB_OPT_WCN_ISSUE_INFO			(1<<19)
#define DB_OPT_DUMMY_DUMP			(1<<20)
#define DB_OPT_PID_MEMORY_INFO			(1<<21)
#define DB_OPT_VM_OOME_HPROF			(1<<22)
#define DB_OPT_PID_SMAPS			(1<<23)
#define DB_OPT_PROC_CMDQ_INFO			(1<<24)
#define DB_OPT_PROC_USKTRK			(1<<25)
#define DB_OPT_SF_RTT_DUMP			(1<<26)
#define DB_OPT_PAGETYPE_INFO			(1<<27)
#define DB_OPT_DUMPSYS_PROCSTATS		(1<<28)
#define DB_OPT_DUMP_DISPLAY			(1<<29)
#define DB_OPT_NATIVE_BACKTRACE			(1<<30)
#define DB_OPT_AARCH64				(1<<31)

#define aee_kernel_warning(module, msg...) \
	pr_warn_ratelimited(msg)

#define aee_kernel_warning_api(file, line, db_opt, module, msg...) \
	pr_warn_ratelimited(msg)

#define aee_kernel_exception(module, msg...) \
	WARN(1, msg)

#define aee_kernel_exception_api(file, line, db_opt, module, msg...) \
	WARN(1, msg)

#define aee_kernel_reminding(module, msg...) \
	pr_debug(msg)

#define aee_kernel_exception_api_func(file, line, db_opt, module, msg...) \
	WARN(1, msg)

#define aee_kernel_warning_api_func(file, line, db_opt, module, msg...) \
	pr_warn_ratelimited(msg)

#define aee_kernel_reminding_api(file, line, db_opt, module, msg...) \
	pr_debug(msg)

#define aee_sram_printk(msg...) \
	pr_debug(msg)

static inline void aed_md_exception_api(const int *log, int log_size, const int *phy,
										int phy_size, const char *detail, const int db_opt)
{
	pr_err("AED MD EXCEPTION: %s (opt=0x%x, log_sz=%d, phy_sz=%d)\n", 
		   detail, db_opt, log_size, phy_size);
}

static inline void aed_md32_exception_api(const int *log, int log_size, const int *phy,
										  int phy_size, const char *detail, const int db_opt)
{
	pr_err("AED MD32 EXCEPTION: %s (opt=0x%x, log_sz=%d, phy_sz=%d)\n", 
		   detail, db_opt, log_size, phy_size);
}

static inline void aed_scp_exception_api(const int *log, int log_size, const int *phy,
										 int phy_size, const char *detail, const int db_opt)
{
	pr_err("AED SCP EXCEPTION: %s (opt=0x%x, log_sz=%d, phy_sz=%d)\n", 
		   detail, db_opt, log_size, phy_size);
}

static inline void aed_combo_exception_api(const int *log, int log_size, const int *phy,
										   int phy_size, const char *detail, const int db_opt)
{
	pr_err("AED COMBO EXCEPTION: %s (opt=0x%x, log_sz=%d, phy_sz=%d)\n", 
		   detail, db_opt, log_size, phy_size);
}

static inline void aed_common_exception_api(const char *assert_type, const int *log, int log_size, 
											const int *phy, int phy_size, const char *detail, const int db_opt)
{
	pr_err("AED COMMON EXCEPTION [%s]: %s (opt=0x%x, log_sz=%d, phy_sz=%d)\n", 
		   assert_type, detail, db_opt, log_size, phy_size);
}

#define aed_md_exception(log, log_size, phy, phy_size, detail) \
	aed_md_exception_api(log, log_size, phy, phy_size, detail, DB_OPT_DEFAULT)

#define aed_md32_exception(log, log_size, phy, phy_size, detail) \
	aed_md32_exception_api(log, log_size, phy, phy_size, detail, DB_OPT_DEFAULT)

#define aed_scp_exception(log, log_size, phy, phy_size, detail) \
	aed_scp_exception_api(log, log_size, phy, phy_size, detail, DB_OPT_DEFAULT)

#define aed_combo_exception(log, log_size, phy, phy_size, detail) \
	aed_combo_exception_api(log, log_size, phy, phy_size, detail, DB_OPT_DEFAULT)

#define aed_common_exception(assert_type, log, log_size, phy, phy_size, detail) \
	aed_common_exception_api(assert_type, log, log_size, phy, phy_size, detail, DB_OPT_DEFAULT)

#endif/* __AEE_H__ */
