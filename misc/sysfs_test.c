#include <linux/init.h>
#include <linux/module.h>
#include <linux/sysfs.h>
#include <linux/slab.h>
#include <linux/device.h>

static int foo;

static ssize_t foo_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	return sprintf(buf, "%d\n", foo);
}

static ssize_t foo_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	sscanf(buf, "%du", &foo);
	return count;
}
static DEVICE_ATTR(foo, 0644, foo_show, foo_store);

static struct attribute *foo_attrs[] = {
	&dev_attr_foo.attr,
	NULL,
};

static struct attribute_group foo_attr_group = {
	.attrs = foo_attrs,
};

static const struct attribute_group *dev_attr_groups[] = {
        &foo_attr_group,
        NULL,
};

static struct device *dev;

static void test_release(struct device *dev)
{
}

static int __init test_init(void)
{
	int ret;
	char *name = "test";

	dev = kzalloc(sizeof(struct device), GFP_KERNEL);
	if (!dev) 
		return -ENOMEM;

	dev_set_name(dev, "%s", name);
	dev->groups = dev_attr_groups;
	dev->release = test_release;

	ret = device_register(dev);
	if (ret)
		return ret;

	return 0;
}

static void __exit test_exit(void)
{
	device_unregister(dev);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
