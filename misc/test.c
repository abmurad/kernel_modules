#include <linux/init.h>
#include <linux/module.h>
#include <linux/cpumask.h>

static char* cpus = "0";
module_param(cpus, charp, S_IRUGO);

static cpumask_var_t mask;

static int __init test_init(void)
{
	int cpu;

	alloc_cpumask_var(&mask, GFP_KERNEL);
	cpumask_clear(mask);

	cpumask_parse(cpus, mask);
	if (cpumask_empty(mask))
		pr_info("mask is empty!\n");

	for_each_cpu(cpu, mask)
		pr_info("cpu%d\n", cpu);

	return 0;
}

static void __exit test_exit(void)
{
	free_cpumask_var(mask);
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
