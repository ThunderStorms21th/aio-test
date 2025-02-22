#ifndef __ASM_TOPOLOGY_H
#define __ASM_TOPOLOGY_H

#ifdef CONFIG_SMP

#include <linux/cpumask.h>

struct cpu_topology {
	int thread_id;
	int core_id;
	int cluster_id;
	cpumask_t thread_sibling;
	cpumask_t core_sibling;
};

extern struct cpu_topology cpu_topology[NR_CPUS];

#define topology_physical_package_id(cpu)	(cpu_topology[cpu].cluster_id)
#define topology_core_id(cpu)		(cpu_topology[cpu].core_id)
#define topology_core_cpumask(cpu)	(&cpu_topology[cpu].core_sibling)
#define topology_thread_cpumask(cpu)	(&cpu_topology[cpu].thread_sibling)

void init_cpu_topology(void);
int get_current_cpunum(void);
void store_cpu_topology(unsigned int cpuid);
const struct cpumask *cpu_coregroup_mask(int cpu);

#define arch_scale_freq_capacity arm_arch_scale_freq_capacity
struct sched_domain;
extern
unsigned long arm_arch_scale_freq_capacity(int cpu);

DECLARE_PER_CPU(atomic_long_t, cpu_freq_capacity);

#define arch_scale_cpu_capacity arm_arch_scale_cpu_capacity
extern unsigned long arm_arch_scale_cpu_capacity(struct sched_domain *sd, int cpu);

#else

static inline void init_cpu_topology(void) { }
static inline void store_cpu_topology(unsigned int cpuid) { }

#endif

#include <asm-generic/topology.h>

#endif /* _ASM_ARM_TOPOLOGY_H */
