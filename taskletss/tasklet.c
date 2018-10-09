#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/interrupt.h>
#include<linux/fs.h> 
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h> // for dev_t
#include<linux/cdev.h>   // for cdev_add(), cdev_alloc()

static int tasklet_major = 0;
char data[]="Tasklet Function";

static void tasklet_operation(unsigned long );

DECLARE_TASKLET(tasklet, tasklet_operation, (unsigned long) &data);


void tasklet_operation(unsigned long data)
{
	printk("%s\n", (char *)data);
}

ssize_t tasklet_read(struct file *filp, char __user *buf, size_t count, loff_t *pos)
{
	tasklet_schedule(&tasklet);
	return 0;
}

ssize_t tasklet_write(struct file *filp, const char __user *buf, size_t count,
                loff_t *pos)
{
 	printk("%s\n",__FUNCTION__);
	return 0;
}

struct file_operations tasklet_ops = {
	.owner = THIS_MODULE,
 	.read = tasklet_read,
	.write = tasklet_write,
};

void init_chrdev(dev_t dev_num)
{
	struct cdev *t_dev;

	t_dev = cdev_alloc();
	t_dev->ops = &tasklet_ops;

	cdev_add(t_dev, dev_num, 1);
}

static int init_tasklet( void )
{
	int result;
	dev_t dev_num;

        result = alloc_chrdev_region(&dev_num, 0, 1, "Tasklet");
	if(result < 0)
		return result;
	else
	{
		tasklet_major = MAJOR(dev_num);
		printk("Registered Successfully with MAJOR %d,Create character device node\n",tasklet_major);

		init_chrdev(dev_num);
	}

	return 0;
}

static void exit_tasklet( void )
{
	unregister_chrdev(tasklet_major, "tasklet");
	tasklet_kill(&tasklet);
}

MODULE_LICENSE("Dual BSD/GPL");

module_init(init_tasklet);
module_exit(exit_tasklet);
