/*
 * bogo scheduler:
 * Round robin scheduler which picks random tasks to run.
 * Inspired by bogo sort.
 *
 * Written by Elias Carter
 */

#include "sched.h"

#include <linux/random.h>
#include <linux/slab.h>

//TODO: dont piggyback off the RR timeslice value for the RT scheduler
int bogo_rr_timeslice = RR_TIMESLICE;

/*
 * How many tasks can we hold in the bogo
 * runqueue initially.
 */
#define arry_init_sz 10

static void update_curr_bogo(struct rq *rq);

void init_bogo_rq(struct bogo_rq *bogo_rq)
{
	unsigned int size;
	size = arry_init_sz * sizeof(struct task_struct*);
	bogo_rq->task_arry = kmalloc(size, GFP_NOWAIT);
	bogo_rq->nr_running = 0;
}

static void
enqueue_task_bogo(struct rq *rq, struct task_struct *p, int flags)
{
	unsigned int nr_running;
	struct bogo_rq * bogo_rq;
	struct task_struct **task_arry;

	bogo_rq = &rq->bogo;
	task_arry = bogo_rq->task_arry;
	nr_running = bogo_rq->nr_running;


	//TODO: realloc task_arry if we run out of room

	task_arry[nr_running] = p;
	nr_running++;
}

static void
dequeue_task_bogo(struct rq *rq, struct task_struct *p, int flags)
{
	struct bogo_rq *bogo_rq;

	bogo_rq = &rq->bogo;
	bogo_rq->nr_running--;
}

static void yield_task_bogo(struct rq *rq)
{
}

static void
check_preempt_curr_bogo(struct rq *rq, struct task_struct *p, int flags)
{
	/*
	 * New tasks never preempt the currently running one.
	 * The only way a task is preempted is when its time
	 * slice runs out.
	 */
}

static struct task_struct *
pick_next_task_bogo(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
	unsigned int rand, next_index;
	struct bogo_rq *bogo_rq;
	struct task_struct *next;

	next = NULL;

	bogo_rq = &rq->bogo;
	if (bogo_rq->nr_running) {
		get_random_bytes_arch(&rand, sizeof(rand));
		next_index = rand % bogo_rq->nr_running;
		next = bogo_rq->task_arry[next_index];
	}

	return next;
}

static void put_prev_task_bogo(struct rq *rq, struct task_struct *prev)
{
}

#ifdef CONFIG_SMP
static int
select_task_rq_bogo(struct task_struct *p, int cpu, int sd_flag, int flags)
{
	return task_cpu(p); /* don't migrate tasks for now */
}
#endif /* CONFIG_SMP */

static void set_curr_task_bogo(struct rq *rq)
{
}

static void task_tick_bogo(struct rq *rq, struct task_struct *curr, int queued)
{
	update_curr_bogo(rq);

	if (--curr->rt.time_slice)
		return;

	curr->rt.time_slice = bogo_rr_timeslice;
	resched_curr(rq);
}

static unsigned int
get_rr_interval_bogo(struct rq *rq, struct task_struct *task)
{
	return bogo_rr_timeslice;
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
	/* TODO: timekeeping */
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
