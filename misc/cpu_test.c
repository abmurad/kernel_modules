#include <linux/init.h>
#include <linux/module.h>
#include <linux/smp.h>

static int __init cputest_init(void)
{
    int cpu = smp_processor_id();
    printk(KERN_ALERT "cpu: %d\n", cpu);
	return 0;
}

static void __exit cputest_exit(void)
{
    int cpu = smp_processor_id();
    printk(KERN_ALERT "cpu: %d\n", cpu);
}

module_init(cputest_init);
module_exit(cputest_exit);
