#include <linux/init.h>
#include <linux/module.h>
#include <asm/irq_regs.h>

static int __init test_init(void)
{
	struct pt_regs *regs = get_irq_regs();
	if (regs) {
		pr_info("bx:\t%08lx\n", regs->bx);
	}
	
	return 0;
}

static void __exit test_exit(void)
{
}

module_init(test_init);
module_exit(test_exit);
