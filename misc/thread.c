#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

static int __init test_init(void)
{
	struct thread_struct *thread = &current->thread;
	pr_info("current %x\n" , current);
	pr_info("sp0:\t0x%08lx\n", thread->sp0);
	pr_info("sp:\t0x%08lx\n", thread->sp);
	pr_info("cs:\t0x%08lx\n", thread->sysenter_cs);
	pr_info("ip:\t0x%08lx\n", thread->ip);
	pr_info("gs:\t0x%08lx\n", thread->gs);
	
	return 0;
}

static void __exit test_exit(void)
{
}

module_init(test_init);
module_exit(test_exit);
