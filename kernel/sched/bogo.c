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
	.rq_online              = rq_online_bogo,
	.rq_offline             = rq_offline_bogo,
	.task_woken		= task_woken_bogo,
	.switched_from		= switched_from_bogo,
#endif

	.set_curr_task          = set_curr_task_bogo,
	.task_tick		= task_tick_bogo,

	.get_rr_interval	= get_rr_interval_bogo,

	.prio_changed		= prio_changed_bogo,
	.switched_to		= switched_to_bogo,
	.update_curr		= update_curr_bogo,
};
