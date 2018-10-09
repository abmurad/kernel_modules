#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

static int test_probe(struct platform_device *pdev)
{
	printk("probe\n");
	try_module_get(pdev->dev.driver->owner);
	return 0;
}

static int test_remove(struct platform_device *pdev)
{
	printk("remove\n");
	module_put(pdev->dev.driver->owner);
	return 0;
}

static struct platform_driver test_driver = {
	.probe		= test_probe,
	.remove		= test_remove,
	.driver		= {
		.name	= "test",
		.owner	= THIS_MODULE,
	},
};

static int __init test_driver_init(void)
{
	return platform_driver_register(&test_driver);
}

static void __exit test_driver_exit(void)
{
	platform_driver_unregister(&test_driver);
}

module_init(test_driver_init);
module_exit(test_driver_exit);

MODULE_LICENSE("GPL");
