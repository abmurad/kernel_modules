#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/interrupt.h>
#include<linux/fs.h> 
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h> // for dev_t
#include<linux/cdev.h>   // for cdev_add(), cdev_alloc()
#include<linux/workqueue.h>

static int workqueue_major = 0;

static struct work_struct simple_work;

static void func_workqueue( void *ptr)
{
	printk("%s\n", __FUNCTION__);
}

ssize_t workqueue_read(struct file *filp, char __user *buf, size_t count, loff_t *pos)
{
	schedule_work(&simple_work);
	return 0;
}

ssize_t workqueue_write(struct file *filp, const char __user *buf, size_t count,
                loff_t *pos)
{
 	printk("%s\n",__FUNCTION__);
	return 0;
}

struct file_operations workqueue_ops = {
	.owner = THIS_MODULE,
 	.read = workqueue_read,
	.write = workqueue_write,
};

void init_chrdev(dev_t dev_num)
{
	struct cdev *t_dev;

	t_dev = cdev_alloc();
	t_dev->ops = &workqueue_ops;

	cdev_add(t_dev, dev_num, 1);
}

static int init_workqueue( void )
{
	int result;
	dev_t dev_num;

        result = alloc_chrdev_region(&dev_num, 0, 1, "Workqueue");
	if(result < 0)
		return result;
	else
	{
		workqueue_major = MAJOR(dev_num);
		printk("Registered Successfully with MAJOR %d,Create character device node\n",workqueue_major);

		init_chrdev(dev_num);
	
                INIT_WORK(&simple_work, &func_workqueue);
	}

	return 0;
}

static void exit_workqueue( void )
{
	unregister_chrdev(workqueue_major, "Workqueue");
}

MODULE_LICENSE("Dual BSD/GPL");

module_init(init_workqueue);
module_exit(exit_workqueue);
