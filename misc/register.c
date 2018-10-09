#include <linux/init.h>
#include <linux/module.h>
#include <linux/notifier.h>

int test_notifier_register(struct notifier_block *nb);
int test_notifier_unregister(struct notifier_block *nb);

static int test_call(struct notifier_block *blk, unsigned long code, void *_param)
{
	int *param = _param;
	pr_info("code: %ld, param: %d\n", code, *param);
	return 0;
}

static struct notifier_block test_block = {
	.notifier_call = test_call,
};

static int __init test_init(void)
{
	return test_notifier_register(&test_block);
}

static void __exit test_exit(void)
{
	test_notifier_unregister(&test_block);
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
