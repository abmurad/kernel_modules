#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/platform_device.h>

static char tmp[32]="sdfdfgdgfgf";

ssize_t echo_read(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	return simple_read_from_buffer(buf, count, ppos, tmp, strlen(tmp));
}

ssize_t echo_write(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	return simple_write_to_buffer(tmp, sizeof(tmp) - 1, ppos, buf, count);
}

static const struct file_operations echo_device_fops = {
	.owner	= THIS_MODULE,
	.read	= echo_read,
	.write	= echo_write,
};

static struct miscdevice echo_device = {
	.minor  = MISC_DYNAMIC_MINOR,
	.name   = "echo",
	.fops   = &echo_device_fops,
	.mode   = 0666,
};

static int test_probe(struct platform_device *pdev)
{
	return misc_register(&echo_device);
}

static int test_remove(struct platform_device *pdev)
{
	misc_deregister(&echo_device);
	return 0;
}

static struct platform_driver test_driver = {
	.probe		= test_probe,
	.remove		= test_remove,
	.driver		= {
		.name	= "test_device",
		.owner	= THIS_MODULE,
	},
};

static void test_release(struct device *dev)
{
}

static struct platform_device test_device = {
	.name = "test_device",
	.id = 0,
	.dev = {
		.release = test_release,
	},
};

static int __init test_driver_init(void)
{
	int ret;
	ret = platform_device_register(&test_device);
	ret = platform_driver_register(&test_driver);
	return ret;
}

static void __exit test_driver_exit(void)
{
	platform_device_unregister(&test_device);
	platform_driver_unregister(&test_driver);
}

module_init(test_driver_init);
module_exit(test_driver_exit);
MODULE_LICENSE("GPL");
