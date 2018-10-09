#include <linux/init.h>
#include <linux/module.h>

static int val = 0;
module_param(val, int, 0644);
static int param = 0;
module_param(param, int, 0644);
int call_test_notifiers(int val, void *v);

static int __init test_init(void)
{
	return call_test_notifiers(val, &param);
}

static void __exit test_exit(void)
{
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
