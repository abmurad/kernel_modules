#include <linux/module.h>
#include <linux/init.h>

static int __init test_init(void)
{
	struct module *owner = THIS_MODULE;
	try_module_get(owner);
	return 0;
}

static void __exit test_exit(void)
{
	struct module *owner = THIS_MODULE;
	module_put(owner);
}

module_init(test_init);
module_exit(test_exit);
