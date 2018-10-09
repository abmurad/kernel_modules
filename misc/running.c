#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/kthread.h>

static struct task_struct *task;

static int thread(void *data)
{
        while (!kthread_should_stop()) {
		struct task_struct *tsk;
		
		for_each_process(tsk) {
			if (tsk->flags & PF_KSWAPD)
				continue;

			if (tsk->state == TASK_RUNNING)
				pr_info("%u\t%s\t is running!\n", tsk->pid, tsk->comm);
		}
		msleep_interruptible(100);
	}

        return 0;
}

static int __init test_init(void)
{
	task = kthread_run(thread, NULL, "test");
	if (IS_ERR(task)) {
		pr_err("create kthread failed!\n");
		return PTR_ERR(task);
	}
	return 0;
}

static void __exit test_exit(void)
{
	kthread_stop(task);
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
