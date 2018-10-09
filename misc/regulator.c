#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/delay.h>

struct test_device {
	int test;
	struct device dev;
};
static struct test_device *tdev;

static void test_release(struct device *dev)
{
	pr_info("%s\n", __func__);
	//struct test_device *t = container_of(dev, struct test_device, dev);
	//pr_info("%s: kfree %p\n", __func__, t);
	//kfree(t);
	//t = NULL;
}

static struct class regulator_class = {
        .name = "power",
        .dev_release = test_release,
};

static int __init test_init(void)
{
	int ret;
	char *name = "power";

	tdev = kzalloc(sizeof(struct test_device), GFP_KERNEL);
	if (!tdev) 
		return -ENOMEM;

	dev_set_name(&tdev->dev, "%s", name);
	tdev->dev.class = &regulator_class;
	//tdev->dev.release = test_release;

	//ret = class_register(&re);
	ret = device_register(&tdev->dev);
	if (ret)
		goto err;

	return 0;

err:
	put_device(&tdev->dev);
	//msleep_interruptible(1000);
	//pr_info("%s: tdev %p\n", __func__, tdev);
	//kfree(tdev);
	return ret;
}

static void __exit test_exit(void)
{
	device_unregister(&tdev->dev);
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
