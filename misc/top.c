#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/kthread.h>

struct task_struct *task = NULL ;;

static int thread(void *data)
{
		while (!kthread_should_stop()) {

				int cr3 = 1 ;

				for(task = &init_task; cr3 || task != &init_task ; task = next_task(task)) {

						cr3 = 0;

						printk(" %10d %10d %3d\t%s\n" , task -> pid , task -> parent -> pid , task -> state ,task -> comm ) ;

				}

				msleep_interruptible(100);

				printk("\r");
		}


		return 0 ;

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

MODULE_AUTHOR("UMARAJU SRABOJU");
