#include <linux/init.h>
#include <linux/module.h>
#include <linux/netdevice.h>

static int netdev_event_handler(struct notifier_block *nb,
		unsigned long event, void *ptr)
{
	struct net_device *dev = ptr;

	if (dev->name)
		pr_info("dev->name: %c\n", dev->name[0]);

	switch (event) {
		case NETDEV_UP:
			pr_info("netdev up\n");
			break;
		case NETDEV_DOWN:
		case NETDEV_UNREGISTER:
			pr_info("netdev down\n");
			break;
	}
	return NOTIFY_DONE;
}

static struct notifier_block netdev_notifier_blk = {
	.notifier_call = netdev_event_handler,
};

static int __init my_init(void)
{
	register_netdevice_notifier(&netdev_notifier_blk);
	return 0;
}

static void __exit my_exit(void)
{
	unregister_netdevice_notifier(&netdev_notifier_blk);
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
