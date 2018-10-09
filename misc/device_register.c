#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kdev_t.h>

#define TEST_MAJOR 246

static void test_release(struct device *dev)
{
       printk(KERN_DEBUG "test device released\n");
}

static struct device test_device = {
	.init_name = "test",
	.devt = MKDEV(TEST_MAJOR, 0),
	.release = test_release,
};

static int __init test_init(void)
{
	return device_register(&test_device);
}

static void __exit test_exit(void)
{
	device_unregister(&test_device);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
