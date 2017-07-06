/*
 * bogo scheduler:
 * Round robin scheduler which picks random tasks to run.
 * Inspired by bogo sort.
 *
 * Written by Elias Carter
 */

#include "sched.h"

int bogo_rr_timeslice = 100;

static void
enqueue_task_bogo(struct rq *rq, struct task_struct *p, int flags)
{
}

static void
dequeue_task_bogo(struct rq *rq, struct task_struct *p, int flags)
{
}

static void yield_task_bogo(struct rq *rq)
{
}

static void
check_preempt_curr_bogo(struct rq *rq, struct task_struct *p, int flags)
{
}

static struct task_struct *
pick_next_task_bogo(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
}

static void put_prev_task_bogo(struct rq *rq, struct task_struct *prev)
{
}

#ifdef CONFIG_SMP
static int
select_task_rq_bogo(struct task_struct *p, int cpu, int sd_flag, int flags)
{
}
#endif /* CONFIG_SMP */

static void set_curr_task_bogo(struct rq *rq)
{
}

static void task_tick_bogo(struct rq *rq, struct task_struct *curr, int queued)
{
}

static unsigned int
get_rr_interval_bogo(struct rq *rq, struct task_struct *task)
{
}

static void
prio_changed_bogo(struct rq *rq, struct task_struct *p, int oldprio)
{
}

static void switched_to_bogo(struct rq *rq, struct task_struct *p)
{
}

static void update_curr_bogo(struct rq *rq)
{
}

const struct sched_class bogo_sched_class = {
	.next			= &rt_sched_class,

	.enqueue_task		= enqueue_task_bogo,
	.dequeue_task		= dequeue_task_bogo,
	.yield_task		= yield_task_bogo,

	.check_preempt_curr	= check_preempt_curr_bogo,

	.pick_next_task		= pick_next_task_bogo,
	.put_prev_task		= put_prev_task_bogo,

#ifdef CONFIG_SMP
	.select_task_rq		= select_task_rq_bogo,
	.set_cpus_allowed       = set_cpus_allowed_common,
#endif

	.set_curr_task          = set_curr_task_bogo,
	.task_tick		= task_tick_bogo,

	.get_rr_interval	= get_rr_interval_bogo,

	.prio_changed		= prio_changed_bogo,
	.switched_to		= switched_to_bogo,
	.update_curr		= update_curr_bogo,
};
