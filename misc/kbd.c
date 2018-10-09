#include <linux/init.h>
#include <linux/module.h>
#include <linux/keyboard.h>

static int test_call(struct notifier_block *blk, unsigned long code, void *_param)
{
	struct keyboard_notifier_param *param = _param;
	switch (code) {
	case KBD_KEYCODE:
		pr_info("%s %u %d  %d\n", __func__, param->value , param->down , param->shift);
		break;
	default:
		break;
	}
	return 0;
}

static struct notifier_block test_block = {
	.notifier_call = test_call,
};

static int __init test_init(void)
{
	return register_keyboard_notifier(&test_block);
}

static void __exit test_exit(void)
{
	unregister_keyboard_notifier(&test_block);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
