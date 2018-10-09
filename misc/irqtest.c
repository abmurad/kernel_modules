#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

static int irq;
module_param(irq, int, 0644);
static char *name;
module_param(name, charp, 0644);

static irqreturn_t handler(int irq, void *dev_id)
{
	pr_info("interrupt number %d --jiffies:%ld\n", irq, jiffies);
	return IRQ_NONE;
}

static int __init myirqtest_init(void)
{
	if (request_irq(irq, &handler, IRQF_SHARED, name, &irq)) {
		pr_err("myirqtest: cannot register IRQ %d\n", irq);
		return -EIO;
	}
	pr_info("%s Request on IRQ %d succeeded\n", name, irq);

	return 0;
}

static void __exit myirqtest_exit(void)
{
	free_irq(irq, &irq);
}

module_init(myirqtest_init);
module_exit(myirqtest_exit);
MODULE_LICENSE("GPL");
