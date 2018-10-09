#include <linux/init.h>
#include <linux/module.h>
#include <linux/bio.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched/signal.h>
/* struct bio defined in linux/blk_types.h */

static struct task_struct *biotest;

static int biotest_thread(void *data)
{
	struct bio *bio;
	struct task_struct *tsk;

	while (!kthread_should_stop()) {

	for (tsk = &init_task ; (tsk = next_task(tsk)) != &init_task ; ){
			if (tsk->bio_list) {
				if (!bio_list_empty(tsk->bio_list)) {
					bio = bio_list_peek(tsk->bio_list);
					if (bio)
						pr_info("tsk->comm: %s, bi_rw: %lu\n", tsk->comm, bio->bi_rw);
				}
			}

		}

		msleep_interruptible(100);
	}

	return 0;
}

static int __init biotest_init(void)
{
	biotest = kthread_run(biotest_thread, NULL, "biotest");
	if (IS_ERR(biotest)) {
		pr_err("create kthread failed!\n");
		return PTR_ERR(biotest);
	}

	return 0;
}

static void __exit biotest_exit(void)
{
	kthread_stop(biotest);
}

module_init(biotest_init);
module_exit(biotest_exit);
MODULE_LICENSE("GPL");
