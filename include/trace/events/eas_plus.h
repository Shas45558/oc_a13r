/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2019 MediaTek Inc.
 */

#ifdef CONFIG_MTK_SCHED_EXTENSION
TRACE_EVENT(sched_compute_energy,

	TP_PROTO(int dst_cpu, struct cpumask *pd_mask,
		unsigned long energy, unsigned long max_util, unsigned long sum_util),

	TP_ARGS(dst_cpu, pd_mask, energy, max_util, sum_util),

	TP_STRUCT__entry(
		__field(int, dst_cpu)
		__field(long, cpu_mask )
		__field(unsigned long, energy)
		__field(unsigned long, max_util)
		__field(unsigned long, sum_util)
		),

	TP_fast_assign(
		__entry->dst_cpu    = dst_cpu;
		__entry->cpu_mask   = pd_mask->bits[0];
		__entry->energy     = energy;
		__entry->max_util   = max_util;
		__entry->sum_util   = sum_util;
	),

	TP_printk("dst_cpu=%d mask=0x%lx energy=%lu max_util=%lu sum_util=%lu",
		__entry->dst_cpu,
		__entry->cpu_mask,
		__entry->energy,
		__entry->max_util,
		__entry->sum_util)
);

TRACE_EVENT(sched_energy_util,

	TP_PROTO(int dst_cpu,
		unsigned long max_util, unsigned long sum_util,
		int cpu, unsigned long util_cfs, unsigned long util_cfs_energy,
		unsigned long cpu_util),

	TP_ARGS(dst_cpu, max_util, sum_util, cpu, util_cfs, util_cfs_energy, cpu_util),

	TP_STRUCT__entry(
		__field(int, dst_cpu)
		__field(unsigned long, max_util)
		__field(unsigned long, sum_util)
		__field(int, cpu)
		__field(unsigned long, util_cfs)
		__field(unsigned long, util_cfs_energy)
		__field(unsigned long, cpu_util)
		),

	TP_fast_assign(
		__entry->dst_cpu    = dst_cpu;
		__entry->max_util   = max_util;
		__entry->sum_util   = sum_util;
		__entry->cpu        = cpu;
		__entry->util_cfs   = util_cfs;
		__entry->util_cfs_energy   = util_cfs_energy;
		__entry->cpu_util   = cpu_util;
		),

	TP_printk("dst_cpu=%d max_util=%lu sum_util=%lu cpu=%d util_cfs=%lu util_cfs_energy=%lu cpu_util=%lu",
		__entry->dst_cpu,
		__entry->max_util,
		__entry->sum_util,
		__entry->cpu,
		__entry->util_cfs,
		__entry->util_cfs_energy,
		__entry->cpu_util)
);

TRACE_EVENT(sched_em_cpu_energy,

	TP_PROTO(int opp,
		unsigned long freq,
		unsigned long dyn_pwr,
		unsigned long sum_util, unsigned int opp_cap),

	TP_ARGS(opp, freq, dyn_pwr, sum_util, opp_cap),

	TP_STRUCT__entry(
		__field(int, opp)
		__field(unsigned long, freq)
		__field(unsigned long, dyn_pwr)
		__field(unsigned long, sum_util)
		__field(unsigned int, opp_cap)
	),

	TP_fast_assign(
		__entry->opp        = opp;
		__entry->freq       = freq;
		__entry->dyn_pwr    = dyn_pwr;
		__entry->sum_util   = sum_util;
		__entry->opp_cap    = opp_cap;
	),

	TP_printk("opp=%d freq=%lu dyn_pwr=%lu sum_util=%lu opp_cap=%u",
		__entry->opp,
		__entry->freq,
		__entry->dyn_pwr,
		__entry->sum_util,
		__entry->opp_cap)
);
#endif /* CONFIG_MTK_SCHED_EXTENSION */
