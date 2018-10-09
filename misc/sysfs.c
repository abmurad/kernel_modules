/*
 * some code copy from samples/kobject/kobject-example.c.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

static int foo;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
		char *buf)
{
	return sprintf(buf, "%d\n", foo);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	sscanf(buf, "%du", &foo);
	return count;
}

static struct kobj_attribute foo_attribute =
	__ATTR(foo, 0664, foo_show, foo_store);

static struct attribute *attrs[] = {
	&foo_attribute.attr,
	NULL,
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};

static struct kobject *test_kobj;

static int __init test_init(void)
{
	int retval;

	test_kobj = kobject_create_and_add("test_kobj", kernel_kobj);
	retval = sysfs_create_group(test_kobj, &attr_group);
	return retval;
}

static void __exit test_exit(void)
{
	kobject_put(test_kobj);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
