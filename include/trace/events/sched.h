#undef TRACE_SYSTEM
#define TRACE_SYSTEM sched

#if !defined(_TRACE_SCHED_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_SCHED_H

#include <linux/sched.h>
#include <linux/tracepoint.h>
#include <linux/binfmts.h>

/*
 * Tracepoint for calling kthread_stop, performed to end a kthread:
 */
TRACE_EVENT(sched_kthread_stop,

	TP_PROTO(struct task_struct *t),

	TP_ARGS(t),

	TP_STRUCT__entry(
		__array(	char,	comm,	TASK_COMM_LEN	)
		__field(	pid_t,	pid			)
	),

	TP_fast_assign(
		memcpy(__entry->comm, t->comm, TASK_COMM_LEN);
		__entry->pid	= t->pid;
	),

	TP_printk("comm=%s pid=%d", __entry->comm, __entry->pid)
);

/*
 * Tracepoint for the return value of the kthread stopping:
 */
TRACE_EVENT(sched_kthread_stop_ret,

	TP_PROTO(int ret),

	TP_ARGS(ret),

	TP_STRUCT__entry(
		__field(	int,	ret	)
	),

	TP_fast_assign(
		__entry->ret	= ret;
	),

	TP_printk("ret=%d", __entry->ret)
);

/*
 * Tracepoint for waking up a task:
 */
DECLARE_EVENT_CLASS(sched_wakeup_template,

	TP_PROTO(struct task_struct *p, int success),

	TP_ARGS(__perf_task(p), success),

	TP_STRUCT__entry(
		__array(	char,	comm,	TASK_COMM_LEN	)
		__field(	pid_t,	pid			)
		__field(	int,	prio			)
		__field(	int,	success			)
		__field(	int,	target_cpu		)
	),

	TP_fast_assign(
		memcpy(__entry->comm, p->comm, TASK_COMM_LEN);
		__entry->pid		= p->pid;
		__entry->prio		= p->prio;
		__entry->success	= success;
		__entry->target_cpu	= task_cpu(p);
	),

	TP_printk("comm=%s pid=%d prio=%d success=%d target_cpu=%03d",
		  __entry->comm, __entry->pid, __entry->prio,
		  __entry->success, __entry->target_cpu)
);

DEFINE_EVENT(sched_wakeup_template, sched_wakeup,
	     TP_PROTO(struct task_struct *p, int success),
	     TP_ARGS(p, success));

/*
 * Tracepoint for waking up a new task:
 */
DEFINE_EVENT(sched_wakeup_template, sched_wakeup_new,
	     TP_PROTO(struct task_struct *p, int success),
	     TP_ARGS(p, success));

#ifdef CREATE_TRACE_POINTS
static inline long __trace_sched_switch_state(struct task_struct *p)
{
	long state = p->state;

#ifdef CONFIG_PREEMPT
	/*
	 * For all intents and purposes a preempted task is a running task.
	 */
	if (preempt_count() & PREEMPT_ACTIVE)
		state = TASK_RUNNING | TASK_STATE_MAX;
#endif

	return state;
}
#endif

/*
 * Tracepoint for task switches, performed by the scheduler:
 */
TRACE_EVENT(sched_switch,

	TP_PROTO(struct task_struct *prev,
		 struct task_struct *next),

	TP_ARGS(prev, next),

	TP_STRUCT__entry(
		__array(	char,	prev_comm,	TASK_COMM_LEN	)
		__field(	pid_t,	prev_pid			)
		__field(	int,	prev_prio			)
		__field(	long,	prev_state			)
		__array(	char,	next_comm,	TASK_COMM_LEN	)
		__field(	pid_t,	next_pid			)
		__field(	int,	next_prio			)
	),

	TP_fast_assign(
		memcpy(__entry->next_comm, next->comm, TASK_COMM_LEN);
		__entry->prev_pid	= prev->pid;
		__entry->prev_prio	= prev->prio;
		__entry->prev_state	= __trace_sched_switch_state(prev);
		memcpy(__entry->prev_comm, prev->comm, TASK_COMM_LEN);
		__entry->next_pid	= next->pid;
		__entry->next_prio	= next->prio;
	),

	TP_printk("prev_comm=%s prev_pid=%d prev_prio=%d prev_state=%s%s ==> next_comm=%s next_pid=%d next_prio=%d",
		__entry->prev_comm, __entry->prev_pid, __entry->prev_prio,
		__entry->prev_state & (TASK_STATE_MAX-1) ?
		  __print_flags(__entry->prev_state & (TASK_STATE_MAX-1), "|",
				{ 1, "S"} , { 2, "D" }, { 4, "T" }, { 8, "t" },
				{ 16, "Z" }, { 32, "X" }, { 64, "x" },
				{ 128, "K" }, { 256, "W" }, { 512, "P" }) : "R",
		__entry->prev_state & TASK_STATE_MAX ? "+" : "",
		__entry->next_comm, __entry->next_pid, __entry->next_prio)
);

/*
 * Tracepoint for a task being migrated:
 */
TRACE_EVENT(sched_migrate_task,

	TP_PROTO(struct task_struct *p, int dest_cpu),

	TP_ARGS(p, dest_cpu),

	TP_STRUCT__entry(
		__array(	char,	comm,	TASK_COMM_LEN	)
		__field(	pid_t,	pid			)
		__field(	int,	prio			)
		__field(	int,	orig_cpu		)
		__field(	int,	dest_cpu		)
	),

	TP_fast_assign(
		memcpy(__entry->comm, p->comm, TASK_COMM_LEN);
		__entry->pid		= p->pid;
		__entry->prio		= p->prio;
		__entry->orig_cpu	= task_cpu(p);
		__entry->dest_cpu	= dest_cpu;
	),

	TP_printk("comm=%s pid=%d prio=%d orig_cpu=%d dest_cpu=%d",
		  __entry->comm, __entry->pid, __entry->prio,
		  __entry->orig_cpu, __entry->dest_cpu)
);

/*
 * Tracepoint for a CPU going offline/online:
 */
TRACE_EVENT(sched_cpu_hotplug,

	TP_PROTO(int affected_cpu, int error, int status),

	TP_ARGS(affected_cpu, error, status),

	TP_STRUCT__entry(
		__field(	int,	affected_cpu		)
		__field(	int,	error			)
		__field(	int,	status			)
	),

	TP_fast_assign(
		__entry->affected_cpu	= affected_cpu;
		__entry->error		= error;
		__entry->status		= status;
	),

	TP_printk("cpu %d %s error=%d", __entry->affected_cpu,
		__entry->status ? "online" : "offline", __entry->error)
);

DECLARE_EVENT_CLASS(sched_process_template,

	TP_PROTO(struct task_struct *p),

	TP_ARGS(p),

	TP_STRUCT__entry(
		__array(	char,	comm,	TASK_COMM_LEN	)
		__field(	pid_t,	pid			)
		__field(	int,	prio			)
	),

	TP_fast_assign(
		memcpy(__entry->comm, p->comm, TASK_COMM_LEN);
		__entry->pid		= p->pid;
		__entry->prio		= p->prio;
	),

	TP_printk("comm=%s pid=%d prio=%d",
		  __entry->comm, __entry->pid, __entry->prio)
);

/*
 * Tracepoint for freeing a task:
 */
DEFINE_EVENT(sched_process_template, sched_process_free,
	     TP_PROTO(struct task_struct *p),
	     TP_ARGS(p));


/*
 * Tracepoint for a task exiting:
 */
DEFINE_EVENT(sched_process_template, sched_process_exit,
	     TP_PROTO(struct task_struct *p),
	     TP_ARGS(p));

/*
 * Tracepoint for waiting on task to unschedule:
 */
DEFINE_EVENT(sched_process_template, sched_wait_task,
	TP_PROTO(struct task_struct *p),
	TP_ARGS(p));

/*
 * Tracepoint for a waiting task:
 */
TRACE_EVENT(sched_process_wait,

	TP_PROTO(struct pid *pid),

	TP_ARGS(pid),

	TP_STRUCT__entry(
		__array(	char,	comm,	TASK_COMM_LEN	)
		__field(	pid_t,	pid			)
		__field(	int,	prio			)
	),

	TP_fast_assign(
		memcpy(__entry->comm, current->comm, TASK_COMM_LEN);
		__entry->pid		= pid_nr(pid);
		__entry->prio		= current->prio;
	),

	TP_printk("comm=%s pid=%d prio=%d",
		  __entry->comm, __entry->pid, __entry->prio)
);

/*
 * Tracepoint for do_fork:
 */
TRACE_EVENT(sched_process_fork,

	TP_PROTO(struct task_struct *parent, struct task_struct *child),

	TP_ARGS(parent, child),

	TP_STRUCT__entry(
		__array(	char,	parent_comm,	TASK_COMM_LEN	)
		__field(	pid_t,	parent_pid			)
		__array(	char,	child_comm,	TASK_COMM_LEN	)
		__field(	pid_t,	child_pid			)
	),

	TP_fast_assign(
		memcpy(__entry->parent_comm, parent->comm, TASK_COMM_LEN);
		__entry->parent_pid	= parent->pid;
		memcpy(__entry->child_comm, child->comm, TASK_COMM_LEN);
		__entry->child_pid	= child->pid;
	),

	TP_printk("comm=%s pid=%d child_comm=%s child_pid=%d",
		__entry->parent_comm, __entry->parent_pid,
		__entry->child_comm, __entry->child_pid)
);

/*
 * Tracepoint for exec:
 */
TRACE_EVENT(sched_process_exec,

	TP_PROTO(struct task_struct *p, pid_t old_pid,
		 struct linux_binprm *bprm),

	TP_ARGS(p, old_pid, bprm),

	TP_STRUCT__entry(
		__string(	filename,	bprm->filename	)
		__field(	pid_t,		pid		)
		__field(	pid_t,		old_pid		)
	),

	TP_fast_assign(
		__assign_str(filename, bprm->filename);
		__entry->pid		= p->pid;
		__entry->old_pid	= old_pid;
	),

	TP_printk("filename=%s pid=%d old_pid=%d", __get_str(filename),
		  __entry->pid, __entry->old_pid)
);

/*
 * XXX the below sched_stat tracepoints only apply to SCHED_OTHER/BATCH/IDLE
 *     adding sched_stat support to SCHED_FIFO/RR would be welcome.
 */
DECLARE_EVENT_CLASS(sched_stat_template,

	TP_PROTO(struct task_struct *tsk, u64 delay),

	TP_ARGS(__perf_task(tsk), __perf_count(delay)),

	TP_STRUCT__entry(
		__array( char,	comm,	TASK_COMM_LEN	)
		__field( pid_t,	pid			)
		__field( u64,	delay			)
	),

	TP_fast_assign(
		memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid	= tsk->pid;
		__entry->delay	= delay;
	),

	TP_printk("comm=%s pid=%d delay=%Lu [ns]",
			__entry->comm, __entry->pid,
			(unsigned long long)__entry->delay)
);


/*
 * Tracepoint for accounting wait time (time the task is runnable
 * but not actually running due to scheduler contention).
 */
DEFINE_EVENT(sched_stat_template, sched_stat_wait,
	     TP_PROTO(struct task_struct *tsk, u64 delay),
	     TP_ARGS(tsk, delay));

/*
 * Tracepoint for accounting sleep time (time the task is not runnable,
 * including iowait, see below).
 */
DEFINE_EVENT(sched_stat_template, sched_stat_sleep,
	     TP_PROTO(struct task_struct *tsk, u64 delay),
	     TP_ARGS(tsk, delay));

/*
 * Tracepoint for accounting iowait time (time the task is not runnable
 * due to waiting on IO to complete).
 */
DEFINE_EVENT(sched_stat_template, sched_stat_iowait,
	     TP_PROTO(struct task_struct *tsk, u64 delay),
	     TP_ARGS(tsk, delay));

/*
 * Tracepoint for accounting blocked time (time the task is in uninterruptible).
 */
DEFINE_EVENT(sched_stat_template, sched_stat_blocked,
	     TP_PROTO(struct task_struct *tsk, u64 delay),
	     TP_ARGS(tsk, delay));

/*
 * Tracepoint for recording the cause of uninterruptible sleep.
 */
TRACE_EVENT(sched_blocked_reason,

	TP_PROTO(struct task_struct *tsk),

	TP_ARGS(tsk),

	TP_STRUCT__entry(
		__field( pid_t,	pid	)
		__field( void*, caller	)
		__field( bool, io_wait	)
	),

	TP_fast_assign(
		__entry->pid	= tsk->pid;
		__entry->caller = (void*)get_wchan(tsk);
		__entry->io_wait = tsk->in_iowait;
	),

	TP_printk("pid=%d iowait=%d caller=%pS", __entry->pid, __entry->io_wait, __entry->caller)
);

/*
 * Tracepoint for accounting runtime (time the task is executing
 * on a CPU).
 */
DECLARE_EVENT_CLASS(sched_stat_runtime,

	TP_PROTO(struct task_struct *tsk, u64 runtime, u64 vruntime),

	TP_ARGS(tsk, __perf_count(runtime), vruntime),

	TP_STRUCT__entry(
		__array( char,	comm,	TASK_COMM_LEN	)
		__field( pid_t,	pid			)
		__field( u64,	runtime			)
		__field( u64,	vruntime			)
	),

	TP_fast_assign(
		memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid		= tsk->pid;
		__entry->runtime	= runtime;
		__entry->vruntime	= vruntime;
	),

	TP_printk("comm=%s pid=%d runtime=%Lu [ns] vruntime=%Lu [ns]",
			__entry->comm, __entry->pid,
			(unsigned long long)__entry->runtime,
			(unsigned long long)__entry->vruntime)
);

DEFINE_EVENT(sched_stat_runtime, sched_stat_runtime,
	     TP_PROTO(struct task_struct *tsk, u64 runtime, u64 vruntime),
	     TP_ARGS(tsk, runtime, vruntime));

/*
 * Tracepoint for showing priority inheritance modifying a tasks
 * priority.
 */
TRACE_EVENT(sched_pi_setprio,

	TP_PROTO(struct task_struct *tsk, int newprio),

	TP_ARGS(tsk, newprio),

	TP_STRUCT__entry(
		__array( char,	comm,	TASK_COMM_LEN	)
		__field( pid_t,	pid			)
		__field( int,	oldprio			)
		__field( int,	newprio			)
	),

	TP_fast_assign(
		memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid		= tsk->pid;
		__entry->oldprio	= tsk->prio;
		__entry->newprio	= newprio;
	),

	TP_printk("comm=%s pid=%d oldprio=%d newprio=%d",
			__entry->comm, __entry->pid,
			__entry->oldprio, __entry->newprio)
);

#ifdef CONFIG_DETECT_HUNG_TASK
TRACE_EVENT(sched_process_hang,
	TP_PROTO(struct task_struct *tsk),
	TP_ARGS(tsk),

	TP_STRUCT__entry(
		__array( char,	comm,	TASK_COMM_LEN	)
		__field( pid_t,	pid			)
	),

	TP_fast_assign(
		memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid = tsk->pid;
	),

	TP_printk("comm=%s pid=%d", __entry->comm, __entry->pid)
);
#endif /* CONFIG_DETECT_HUNG_TASK */

DECLARE_EVENT_CLASS(sched_move_task_template,

	TP_PROTO(struct task_struct *tsk, int src_cpu, int dst_cpu),

	TP_ARGS(tsk, src_cpu, dst_cpu),

	TP_STRUCT__entry(
		__field( pid_t,	pid			)
		__field( pid_t,	tgid			)
		__field( pid_t,	ngid			)
		__field( int,	src_cpu			)
		__field( int,	src_nid			)
		__field( int,	dst_cpu			)
		__field( int,	dst_nid			)
	),

	TP_fast_assign(
		__entry->pid		= task_pid_nr(tsk);
		__entry->tgid		= task_tgid_nr(tsk);
		__entry->ngid		= task_numa_group_id(tsk);
		__entry->src_cpu	= src_cpu;
		__entry->src_nid	= cpu_to_node(src_cpu);
		__entry->dst_cpu	= dst_cpu;
		__entry->dst_nid	= cpu_to_node(dst_cpu);
	),

	TP_printk("pid=%d tgid=%d ngid=%d src_cpu=%d src_nid=%d dst_cpu=%d dst_nid=%d",
			__entry->pid, __entry->tgid, __entry->ngid,
			__entry->src_cpu, __entry->src_nid,
			__entry->dst_cpu, __entry->dst_nid)
);

/*
 * Tracks migration of tasks from one runqueue to another. Can be used to
 * detect if automatic NUMA balancing is bouncing between nodes
 */
DEFINE_EVENT(sched_move_task_template, sched_move_numa,
	TP_PROTO(struct task_struct *tsk, int src_cpu, int dst_cpu),

	TP_ARGS(tsk, src_cpu, dst_cpu)
);

DEFINE_EVENT(sched_move_task_template, sched_stick_numa,
	TP_PROTO(struct task_struct *tsk, int src_cpu, int dst_cpu),

	TP_ARGS(tsk, src_cpu, dst_cpu)
);

TRACE_EVENT(sched_swap_numa,

	TP_PROTO(struct task_struct *src_tsk, int src_cpu,
		 struct task_struct *dst_tsk, int dst_cpu),

	TP_ARGS(src_tsk, src_cpu, dst_tsk, dst_cpu),

	TP_STRUCT__entry(
		__field( pid_t,	src_pid			)
		__field( pid_t,	src_tgid		)
		__field( pid_t,	src_ngid		)
		__field( int,	src_cpu			)
		__field( int,	src_nid			)
		__field( pid_t,	dst_pid			)
		__field( pid_t,	dst_tgid		)
		__field( pid_t,	dst_ngid		)
		__field( int,	dst_cpu			)
		__field( int,	dst_nid			)
	),

	TP_fast_assign(
		__entry->src_pid	= task_pid_nr(src_tsk);
		__entry->src_tgid	= task_tgid_nr(src_tsk);
		__entry->src_ngid	= task_numa_group_id(src_tsk);
		__entry->src_cpu	= src_cpu;
		__entry->src_nid	= cpu_to_node(src_cpu);
		__entry->dst_pid	= task_pid_nr(dst_tsk);
		__entry->dst_tgid	= task_tgid_nr(dst_tsk);
		__entry->dst_ngid	= task_numa_group_id(dst_tsk);
		__entry->dst_cpu	= dst_cpu;
		__entry->dst_nid	= cpu_to_node(dst_cpu);
	),

	TP_printk("src_pid=%d src_tgid=%d src_ngid=%d src_cpu=%d src_nid=%d dst_pid=%d dst_tgid=%d dst_ngid=%d dst_cpu=%d dst_nid=%d",
			__entry->src_pid, __entry->src_tgid, __entry->src_ngid,
			__entry->src_cpu, __entry->src_nid,
			__entry->dst_pid, __entry->dst_tgid, __entry->dst_ngid,
			__entry->dst_cpu, __entry->dst_nid)
);

/*
 * Tracepoint for showing tracked load contribution.
 */
TRACE_EVENT(sched_task_load_contrib,

	TP_PROTO(struct task_struct *tsk, unsigned long load_contrib),

	TP_ARGS(tsk, load_contrib),

	TP_STRUCT__entry(
		__array(char, comm, TASK_COMM_LEN)
		__field(pid_t, pid)
		__field(unsigned long, load_contrib)
	),

	TP_fast_assign(
		memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid            = tsk->pid;
		__entry->load_contrib   = load_contrib;
	),

	TP_printk("comm=%s pid=%d load_contrib=%lu",
			__entry->comm, __entry->pid,
			__entry->load_contrib)
);

/*
 * Tracepoint for showing tracked task runnable ratio [0..1023].
 */
TRACE_EVENT(sched_task_runnable_ratio,

	TP_PROTO(struct task_struct *tsk, unsigned long ratio),

	TP_ARGS(tsk, ratio),

	TP_STRUCT__entry(
		__array(char, comm, TASK_COMM_LEN)
		__field(pid_t, pid)
		__field(unsigned long, ratio)
	),

	TP_fast_assign(
	memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid   = tsk->pid;
		__entry->ratio = ratio;
	),

	TP_printk("comm=%s pid=%d ratio=%lu",
			__entry->comm, __entry->pid,
			__entry->ratio)
);

/*
 * Tracepoint for showing tracked rq runnable ratio [0..1023].
 */
TRACE_EVENT(sched_rq_runnable_ratio,

	TP_PROTO(int cpu, unsigned long ratio),

	TP_ARGS(cpu, ratio),

	TP_STRUCT__entry(
		__field(int, cpu)
		__field(unsigned long, ratio)
	),

	TP_fast_assign(
		__entry->cpu   = cpu;
		__entry->ratio = ratio;
	),

	TP_printk("cpu=%d ratio=%lu",
			__entry->cpu,
			__entry->ratio)
);

/*
 * Tracepoint for showing tracked rq runnable ratio [0..1023].
 */
TRACE_EVENT(sched_rq_sysload_ratio,

	TP_PROTO(int cpu, unsigned long ratio),

	TP_ARGS(cpu, ratio),

	TP_STRUCT__entry(
		__field(int, cpu)
		__field(unsigned long, ratio)
	),

	TP_fast_assign(
		__entry->cpu   = cpu;
		__entry->ratio = ratio;
	),

	TP_printk("cpu=%d ratio=%lu",
			__entry->cpu,
			__entry->ratio)
);

/*
 * Tracepoint for showing tracked rq runnable load.
 */
TRACE_EVENT(sched_rq_runnable_load,

	TP_PROTO(int cpu, u64 load),

	TP_ARGS(cpu, load),

	TP_STRUCT__entry(
		__field(int, cpu)
		__field(u64, load)
	),

	TP_fast_assign(
		__entry->cpu  = cpu;
		__entry->load = load;
	),

	TP_printk("cpu=%d load=%llu",
			__entry->cpu,
			__entry->load)
);

TRACE_EVENT(sched_rq_nr_running,

	TP_PROTO(int cpu, unsigned int nr_running, int nr_iowait),

	TP_ARGS(cpu, nr_running, nr_iowait),

	TP_STRUCT__entry(
		__field(int, cpu)
		__field(unsigned int, nr_running)
		__field(int, nr_iowait)
	),

	TP_fast_assign(
		__entry->cpu  = cpu;
		__entry->nr_running = nr_running;
		__entry->nr_iowait = nr_iowait;
	),

	TP_printk("cpu=%d nr_running=%u nr_iowait=%d",
		__entry->cpu,
		__entry->nr_running, __entry->nr_iowait)
);


/*
 * Tracepoint for showing tracked task cpu usage ratio [0..1023].
 */
TRACE_EVENT(sched_task_usage_ratio,

	TP_PROTO(struct task_struct *tsk, unsigned long ratio),

	TP_ARGS(tsk, ratio),

	TP_STRUCT__entry(
		__array(char, comm, TASK_COMM_LEN)
		__field(pid_t, pid)
		__field(unsigned long, ratio)
	),

	TP_fast_assign(
	memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid   = tsk->pid;
		__entry->ratio = ratio;
	),

	TP_printk("comm=%s pid=%d ratio=%lu",
			__entry->comm, __entry->pid,
			__entry->ratio)
);

/*
 * Tracepoint for HMP (CONFIG_SCHED_HMP) task migrations.
 */
#define HMP_MIGRATE_WAKEUP	0
#define HMP_MIGRATE_FORCE	1
#define HMP_MIGRATE_OFFLOAD	2
#define HMP_MIGRATE_IDLE_PULL	3
#define HMP_MIGRATE_FAMILY	4
#define HMP_MIGRATE_INFORM	99

TRACE_EVENT(sched_hmp_migrate,

	TP_PROTO(struct task_struct *tsk, int dest, int force),

	TP_ARGS(tsk, dest, force),

	TP_STRUCT__entry(
		__array(char, comm, TASK_COMM_LEN)
		__field(pid_t, pid)
		__field(int,  dest)
		__field(int,  force)
	),

	TP_fast_assign(
	memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid   = tsk->pid;
		__entry->dest  = dest;
		__entry->force = force;
	),

	TP_printk("comm=%s pid=%d dest=%d force=%d",
			__entry->comm, __entry->pid,
			__entry->dest, __entry->force)
);

TRACE_EVENT(sched_hmp_migrate_compensation,

	TP_PROTO(struct task_struct *tsk, int dest, int force, int load),

	TP_ARGS(tsk, dest, force, load),

	TP_STRUCT__entry(
		__array(char, comm, TASK_COMM_LEN)
		__field(pid_t, pid)
		__field(int,  dest)
		__field(int,  force)
		__field(int,  load)
	),

	TP_fast_assign(
	memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid   = tsk->pid;
		__entry->dest  = dest;
		__entry->force = force;
		__entry->load = load;
	),

	TP_printk("comm=%s pid=%d dest=%d force=%d, load=%d",
			__entry->comm, __entry->pid,
			__entry->dest, __entry->force, __entry->load)
);

TRACE_EVENT(sched_hmp_offload_abort,

	TP_PROTO(int cpu, int data, char *label),

	TP_ARGS(cpu,data,label),

	TP_STRUCT__entry(
		__array(char, label, 64)
		__field(int, cpu)
		__field(int, data)
	),

	TP_fast_assign(
		strncpy(__entry->label, label, 64);
		__entry->cpu   = cpu;
		__entry->data = data;
	),

	TP_printk("cpu=%d data=%d label=%s",
		__entry->cpu, __entry->data,
		__entry->label)
);

TRACE_EVENT(sched_hmp_offload_succeed,

	TP_PROTO(int cpu, int dest_cpu),

	TP_ARGS(cpu,dest_cpu),

	TP_STRUCT__entry(
		__field(int, cpu)
		__field(int, dest_cpu)
	),

	TP_fast_assign(
		__entry->cpu   = cpu;
		__entry->dest_cpu = dest_cpu;
	),

	TP_printk("cpu=%d dest=%d",
		__entry->cpu,
		__entry->dest_cpu)
);

/*
 * Tracepoint for waking a polling cpu without an IPI.
 */
TRACE_EVENT(sched_wake_idle_without_ipi,

	TP_PROTO(int cpu),

	TP_ARGS(cpu),

	TP_STRUCT__entry(
		__field(	int,	cpu	)
	),

	TP_fast_assign(
		__entry->cpu	= cpu;
	),

	TP_printk("cpu=%d", __entry->cpu)
);


#ifdef CONFIG_SMP
TRACE_EVENT(sched_contrib_scale_f,

	TP_PROTO(int cpu, unsigned long freq_scale_factor,
		 unsigned long cpu_scale_factor),

	TP_ARGS(cpu, freq_scale_factor, cpu_scale_factor),

	TP_STRUCT__entry(
		__field(int, cpu)
		__field(unsigned long, freq_scale_factor)
		__field(unsigned long, cpu_scale_factor)
	),

	TP_fast_assign(
		__entry->cpu = cpu;
		__entry->freq_scale_factor = freq_scale_factor;
		__entry->cpu_scale_factor = cpu_scale_factor;
	),

	TP_printk("cpu=%d freq_scale_factor=%lu cpu_scale_factor=%lu",
		  __entry->cpu, __entry->freq_scale_factor,
		  __entry->cpu_scale_factor)
);

/*
 * Tracepoint for accounting sched averages for tasks.
 */
TRACE_EVENT(sched_load_avg_task,

	TP_PROTO(struct task_struct *tsk, struct sched_avg *avg),

	TP_ARGS(tsk, avg),

	TP_STRUCT__entry(
		__array( char,	comm,	TASK_COMM_LEN		)
		__field( pid_t,	pid				)
		__field( int,	cpu				)
		__field( unsigned long,	load			)
		__field( unsigned long,	utilization		)
		__field( unsigned int,	runnable_avg_sum	)
		__field( unsigned int,	running_avg_sum		)
		__field( unsigned int,	avg_period		)
	),

	TP_fast_assign(
		memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid			= tsk->pid;
		__entry->cpu			= task_cpu(tsk);
		__entry->load			= avg->load_avg_contrib;
		__entry->utilization		= avg->utilization_avg_contrib;
		__entry->runnable_avg_sum	= avg->runnable_avg_sum;
		__entry->running_avg_sum	= avg->running_avg_sum;
		__entry->avg_period		= avg->avg_period;
	),

	TP_printk("comm=%s pid=%d cpu=%d load=%lu utilization=%lu runnable_avg_sum=%u"
		  " running_avg_sum=%u avg_period=%u",
		  __entry->comm, __entry->pid, __entry->cpu,
		  __entry->load, __entry->utilization,
		  (unsigned int)__entry->runnable_avg_sum,
		  (unsigned int)__entry->running_avg_sum,
		  (unsigned int)__entry->avg_period)
);

/*
 * Tracepoint for accounting sched averages for cpus.
 */
TRACE_EVENT(sched_load_avg_cpu,

	TP_PROTO(int cpu, struct cfs_rq *cfs_rq),

	TP_ARGS(cpu, cfs_rq),

	TP_STRUCT__entry(
		__field( int,	cpu				)
		__field( unsigned long,	load			)
		__field( unsigned long,	utilization		)
	),

	TP_fast_assign(
		__entry->cpu			= cpu;
		__entry->load			= cfs_rq->runnable_load_avg;
		__entry->utilization		= cfs_rq->utilization_load_avg;
	),

	TP_printk("cpu=%d load=%lu utilization=%lu",
		  __entry->cpu, __entry->load, __entry->utilization)
);
#endif /* CONFIG_SMP */

TRACE_EVENT(sched_hp_event_thread_group,

	TP_PROTO(struct task_struct *g_tsk, struct task_struct *tsk, unsigned long g_ratio, int nr_thread_gr, unsigned long load_avg_ratio, char *label),

	TP_ARGS(g_tsk, tsk, g_ratio, nr_thread_gr, load_avg_ratio, label),

	TP_STRUCT__entry(
		__array(char, comm, TASK_COMM_LEN)
		__array(char, comm2, TASK_COMM_LEN)
		__field(pid_t, g_pid)
		__field(pid_t, pid)
		__field(unsigned long, g_ratio)
		__field(int, nr_thread_gr)
		__field(unsigned long, load_avg_ratio)
		__array(char, label, 64)
	),

	TP_fast_assign(
		strncpy(__entry->comm, g_tsk->comm, TASK_COMM_LEN);
		strncpy(__entry->comm2, tsk->comm, TASK_COMM_LEN);
		__entry->g_pid            = g_tsk->pid;
		__entry->pid            = tsk->pid;
		__entry->g_ratio = g_ratio;
		__entry->nr_thread_gr = nr_thread_gr;
		__entry->load_avg_ratio = load_avg_ratio;
		strncpy(__entry->label, label, 64);
	),

	TP_printk("g_comm %s g_pid=%d comm=%s pid=%d group_load=%lu group_cnt=%d avg_ratio=%lu label=%s",
			__entry->comm, __entry->g_pid, __entry->comm2, __entry->pid, __entry->g_ratio,
			__entry->nr_thread_gr, __entry->load_avg_ratio, __entry->label)
);

TRACE_EVENT(sched_hp_event_system_load,

	TP_PROTO(int cpu, int data0, int data1, char *label),

	TP_ARGS(cpu,data0,data1,label),

	TP_STRUCT__entry(
		__array(char, label, 64)
		__field(int, cpu)
		__field(int, data0)
		__field(int, data1)
	),

	TP_fast_assign(
		strncpy(__entry->label, label, 64);
		__entry->cpu   = cpu;
		__entry->data0 = data0;
		__entry->data1 = data1;
	),

	TP_printk("cpu=%d data0=%d data1=%d label=%s",
		__entry->cpu, __entry->data0, __entry->data1,
		__entry->label)
);

/*
 * Tracepoint for sched_tune_config settings
 */
TRACE_EVENT(sched_tune_config,

	TP_PROTO(int boost, int pb_nrg_gain, int pb_cap_gain, int pc_nrg_gain, int pc_cap_gain),

	TP_ARGS(boost, pb_nrg_gain, pb_cap_gain, pc_nrg_gain, pc_cap_gain),

	TP_STRUCT__entry(
		__field( int,	boost		)
		__field( int,	pb_nrg_gain	)
		__field( int,	pb_cap_gain	)
		__field( int,	pc_nrg_gain	)
		__field( int,	pc_cap_gain	)
	),

	TP_fast_assign(
		__entry->boost 	= boost;
		__entry->pb_nrg_gain	= pb_nrg_gain;
		__entry->pb_cap_gain	= pb_cap_gain;
		__entry->pc_nrg_gain	= pc_nrg_gain;
		__entry->pc_cap_gain	= pc_cap_gain;
	),

	TP_printk("boost=%d "
			"pb_nrg_gain=%d pb_cap_gain=%d "
			"pc_nrg_gain=%d pc_cap_gain=%d",
		__entry->boost,
		__entry->pb_nrg_gain, __entry->pb_cap_gain,
		__entry->pc_nrg_gain, __entry->pc_cap_gain)
);

/*
 * Tracepoint for accounting task boosted utilization
 */
TRACE_EVENT(sched_boost_task,

	TP_PROTO(struct task_struct *tsk, unsigned long utilization, unsigned long margin),

	TP_ARGS(tsk, utilization, margin),

	TP_STRUCT__entry(
		__array( char,	comm,	TASK_COMM_LEN		)
		__field( pid_t,		pid			)
		__field( unsigned long,	utilization		)
		__field( unsigned long,	margin			)
	),

	TP_fast_assign(
		memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid		= tsk->pid;
		__entry->utilization	= utilization;
		__entry->margin		= margin;
	),

	TP_printk("comm=%s pid=%d utilization=%lu margin=%lu",
		  __entry->comm, __entry->pid,
		  __entry->utilization,
		  __entry->margin)
);

/*
 * Tracepoint for accounting CPU  boosted utilization
 */
TRACE_EVENT(sched_boost_cpu,

	TP_PROTO(int cpu, unsigned long usage, unsigned long margin),

	TP_ARGS(cpu, usage, margin),

	TP_STRUCT__entry(
		__field( int,		cpu			)
		__field( unsigned long,	usage			)
		__field( unsigned long,	margin			)
	),

	TP_fast_assign(
		__entry->cpu	= cpu;
		__entry->usage	= usage;
		__entry->margin	= margin;
	),

	TP_printk("cpu=%d usage=%lu margin=%lu",
		  __entry->cpu,
		  __entry->usage,
		  __entry->margin)
);

/*
 * Tracepoint for accounting sched group energy
 */
TRACE_EVENT(sched_energy_diff,

	TP_PROTO(struct task_struct *tsk, int scpu, int dcpu, int udelta,
		int nrgb, int nrga, int nrgd, int capb, int capa, int capd,
		int nrgn, int nrgp),

	TP_ARGS(tsk, scpu, dcpu, udelta,
		nrgb, nrga, nrgd, capb, capa, capd,
		nrgn, nrgp),

	TP_STRUCT__entry(
		__array( char,	comm,	TASK_COMM_LEN	)
		__field( pid_t,	pid	)
		__field( int,	scpu	)
		__field( int,	dcpu	)
		__field( int,	udelta	)
		__field( int,	nrgb	)
		__field( int,	nrga	)
		__field( int,	nrgd	)
		__field( int,	capb	)
		__field( int,	capa	)
		__field( int,	capd	)
		__field( int,	nrgn	)
		__field( int,	nrgp	)
	),

	TP_fast_assign(
		memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid		= tsk->pid;
		__entry->scpu 		= scpu;
		__entry->dcpu 		= dcpu;
		__entry->udelta 	= udelta;
		__entry->nrgb 		= nrgb;
		__entry->nrga 		= nrga;
		__entry->nrgd 		= nrgd;
		__entry->capb 		= capb;
		__entry->capa 		= capa;
		__entry->capd 		= capd;
		__entry->nrgn 		= nrgn;
		__entry->nrgp 		= nrgp;
	),

	TP_printk("pid=%d comm=%s "
			"src_cpu=%d dst_cpu=%d usage_delta=%d "
			"nrg_before=%d nrg_after=%d nrg_diff=%d "
			"cap_before=%d cap_after=%d cap_delta=%d "
			"nrg_delta=%d nrg_payoff=%d",
		__entry->pid, __entry->comm,
		__entry->scpu, __entry->dcpu, __entry->udelta,
		__entry->nrgb, __entry->nrga, __entry->nrgd,
		__entry->capb, __entry->capa, __entry->capd,
		__entry->nrgn, __entry->nrgp)
);

/*
 * Tracepoint for schedtune_tasks_update
 */
TRACE_EVENT(sched_tune_tasks_update,

	TP_PROTO(struct task_struct *tsk, int cpu, int tasks, int idx,
		unsigned int boost, unsigned int max_boost),

	TP_ARGS(tsk, cpu, tasks, idx, boost, max_boost),

	TP_STRUCT__entry(
		__array( char,	comm,	TASK_COMM_LEN	)
		__field( pid_t,		pid		)
		__field( int,		cpu		)
		__field( int,		tasks		)
		__field( int,		idx		)
		__field( unsigned int,	boost		)
		__field( unsigned int,	max_boost	)
	),

	TP_fast_assign(
		memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid		= tsk->pid;
		__entry->cpu 		= cpu;
		__entry->tasks		= tasks;
		__entry->idx 		= idx;
		__entry->boost		= boost;
		__entry->max_boost	= max_boost;
	),

	TP_printk("pid=%d comm=%s "
			"cpu=%d tasks=%d idx=%d boost=%u max_boost=%u",
		__entry->pid, __entry->comm,
		__entry->cpu, __entry->tasks, __entry->idx,
		__entry->boost, __entry->max_boost)
);

/*
 * Tracepoint for schedtune_tasks_update
 */
TRACE_EVENT(sched_tune_filter,

	TP_PROTO(int nrg_delta, int cap_delta, int nrg_payoff, int region),

	TP_ARGS(nrg_delta, cap_delta, nrg_payoff, region),

	TP_STRUCT__entry(
		__field( int,	nrg_delta	)
		__field( int,	cap_delta	)
		__field( int,	nrg_payoff	)
		__field( int,	region		)
	),

	TP_fast_assign(
		__entry->nrg_delta	= nrg_delta;
		__entry->cap_delta	= cap_delta;
		__entry->nrg_payoff	= nrg_payoff;
		__entry->region		= region;
	),

	TP_printk("nrg_delta=%d cap_delta=%d nrg_payoff=%d region=%d",
		__entry->nrg_delta, __entry->cap_delta,
		__entry->nrg_payoff, __entry->region)
);

/*
 * Tracepoint for schedtune_boostgroup_update
 */
TRACE_EVENT(sched_tune_boostgroup_update,

	TP_PROTO(int cpu, int variation, int max_boost),

	TP_ARGS(cpu, variation, max_boost),

	TP_STRUCT__entry(
		__field( int,	cpu		)
		__field( int,	variation	)
		__field( int,	max_boost	)
	),

	TP_fast_assign(
		__entry->cpu		= cpu;
		__entry->variation	= variation;
		__entry->max_boost	= max_boost;
	),

	TP_printk("cpu=%d variation=%d max_boost=%d",
		__entry->cpu, __entry->variation, __entry->max_boost)
);

#endif /* _TRACE_SCHED_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
