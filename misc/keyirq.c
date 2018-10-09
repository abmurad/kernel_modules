#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>

struct atkbd {
	unsigned char scancode;
	struct work_struct event_work;
};
static struct atkbd *my_dev;
static struct workqueue_struct *my_workqueue;

static void got_char(struct work_struct *work)
{
	struct atkbd *atkbd = container_of(work, struct atkbd, event_work);
	pr_info("Scan Code %x %s.\n", atkbd->scancode & 0x7F,
		atkbd->scancode & 0x80 ? "Released" : "Pressed");
}

static irqreturn_t my_handler(int irq, void *dev_id)
{
	unsigned char status;
	struct atkbd *dev = (struct atkbd *)dev_id;

	/* 
	 * Read keyboard status
	 */
	status = inb(0x64);
	dev->scancode = inb(0x60);

	queue_work(my_workqueue, &dev->event_work);

	return IRQ_HANDLED;
}

static int __init myirqtest_init(void)
{
	my_workqueue = create_workqueue("my_wq");
	my_dev = kmalloc(sizeof(struct atkbd), GFP_KERNEL);
	INIT_WORK(&my_dev->event_work, got_char);

	if (request_irq(1, &my_handler, IRQF_SHARED, "my_irq", my_dev)) {
		pr_err("Cannot register IRQ 1\n");
		return -EIO;
	}

	return 0;
}

static void __exit myirqtest_exit(void)
{
	destroy_workqueue(my_workqueue);
	free_irq(1, my_dev);
	kfree(my_dev);
}

module_init(myirqtest_init);
module_exit(myirqtest_exit);
MODULE_LICENSE("GPL");
