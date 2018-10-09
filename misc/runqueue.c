#include <linux/init.h>
#include <linux/sched/signal.h>

#include <linux/module.h>
#include <linux/sched.h>
#include</usr/src/linux-4.12.9/kernel/sched/sched.h>
#include <linux/percpu-defs.h>
static int __init test_init(void)
{
	struct task_struct *tsk;
	for_each_process(tsk) {
		int cpu = task_cpu(tsk);
		struct rq *rq = cpu_rq(cpu);

		pr_info("nr_running: %d\n", rq->nr_running);
	}
	return 0;
}

static void __exit test_exit(void)
{
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
