/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#ifndef _EXTENSION_EAS_PLUS_H
#define _EXTENSION_EAS_PLUS_H

#include <linux/math64.h>
#include <linux/kobject.h>
#include <linux/cpumask.h>
#include <linux/list_sort.h>

#ifdef CONFIG_MTK_SCHED_EXTENSION
#if defined(CONFIG_ENERGY_MODEL) && defined(CONFIG_CPU_FREQ_GOV_SCHEDUTIL)
struct perf_order_domain {
	struct cpumask cpus;
	struct cpumask possible_cpus;
	struct list_head perf_order_domains;
};

extern void init_perf_order_domains(struct perf_domain *pd);
extern struct list_head perf_order_domains;
#define perf_order_cpu_domain(cpu) (per_cpu(perf_order_cpu_domain, (cpu)))
#define for_each_perf_domain(pod) for_each_perf_domain_descending(pod)
#define for_each_perf_domain_descending(pod) \
		list_for_each_entry(pod, &perf_order_domains, \
					perf_order_domains)

#define for_each_perf_domain_ascending(pod) \
		list_for_each_entry_reverse(pod, &perf_order_domains, \
						perf_order_domains)
bool pod_is_ready(void);
#endif

#ifdef CONFIG_MTK_SCHED_INTEROP
extern bool is_rt_throttle(int cpu);
#endif

#if defined(CONFIG_ENERGY_MODEL) && defined(CONFIG_CPU_FREQ_GOV_SCHEDUTIL)
unsigned int cpu_is_slowest(int cpu);
#endif

#ifdef CONFIG_MTK_SCHED_LB_ENHANCEMENT
bool is_intra_domain(int prev, int target);
#endif

#endif /* CONFIG_MTK_SCHED_EXTENSION */

#endif
