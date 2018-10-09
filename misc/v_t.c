#include <linux/init.h>
#include <linux/module.h>
#include <linux/vt_kern.h>

static int test_call(struct notifier_block *blk, unsigned long code, void *_param)
{
	struct vt_notifier_param *param = _param;
	switch (code) {
	case VT_WRITE: {
		unsigned char c = param->c;
		switch (c) {
		case 'a':
			pr_info("%c", c);
			break;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return NOTIFY_OK;
}

static struct notifier_block test_block = {
	.notifier_call = test_call,
};

static int __init test_init(void)
{
	return register_vt_notifier(&test_block);
}

static void __exit test_exit(void)
{
	unregister_vt_notifier(&test_block);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
