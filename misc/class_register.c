#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>

static struct class test_class = {
	.name = "test",
};

static int __init test_init(void)
{
	return class_register(&test_class);
}

static void __exit test_exit(void)
{
	class_unregister(&test_class);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
