#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

#define TEST_MAJOR 246
#define DEVICE_NAME "test_device"

static struct class *test_class;
static struct device *test_device;

static void test_release(struct device *dev)
{
       printk(KERN_DEBUG "test device released\n");
}

static int test_file_release(struct inode *inode, struct file *file)
{
       printk(KERN_DEBUG "test device file released\n");
       return 0;
}

static struct file_operations test_file_fops = {
	.release = test_file_release,
};

static int __init test_init(void)
{
	test_class = class_create(THIS_MODULE, "test_class");
	test_device = device_create(test_class, NULL, MKDEV(TEST_MAJOR, 0), NULL, DEVICE_NAME);
	test_device->release = test_release;
	return register_chrdev(TEST_MAJOR, DEVICE_NAME, &test_file_fops);
}

static void __exit test_exit(void)
{
	unregister_chrdev(TEST_MAJOR, DEVICE_NAME);
	device_destroy(test_class, MKDEV(TEST_MAJOR, 0));
	class_destroy(test_class);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
