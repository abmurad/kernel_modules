#include <linux/init.h>
#include <linux/module.h>
#include <linux/smp.h>

DEFINE_PER_CPU(int, pctest);

static int __init pctest_init(void)
{
    int cpu = smp_processor_id();
    per_cpu(pctest, cpu) = 1;
    printk(KERN_ALERT "cpu: %d\n", cpu);

    for_each_online_cpu(cpu)
        printk(KERN_ALERT "%d: %d\n", cpu, per_cpu(pctest, cpu));

	return 0;
}

static void __exit pctest_exit(void)
{
}

module_init(pctest_init);
module_exit(pctest_exit);
