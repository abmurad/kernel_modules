#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

static void test_release(struct device *dev)
{
}

static struct platform_device test_device = {
	.name = "test",
	.id = 0,
	.dev = {
		.release = test_release,
	},
};

static int __init test_driver_init(void)
{
	return platform_device_register(&test_device);
}

static void __exit test_driver_exit(void)
{
	platform_device_unregister(&test_device);
}

module_init(test_driver_init);
module_exit(test_driver_exit);

MODULE_LICENSE("GPL");
