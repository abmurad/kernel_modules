#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

static int test_probe(struct platform_device *pdev)
{
	pr_info("%s [%s]\n", __func__, __FILE__);
	return 0;
}

static int test_remove(struct platform_device *pdev)
{
	pr_info("%s [%s]\n", __func__, __FILE__);
	return 0;
}

static struct platform_driver test_driver = {
	.probe		= test_probe,
	.remove		= test_remove,
	.driver		= {
		.name	= "spidev",
		.owner	= THIS_MODULE,
	},
};

static void test_release(struct device *dev)
{
	pr_info("%s [%s]\n", __func__, __FILE__);
}

static struct platform_device test_device = {
	.name = "spidev",
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
