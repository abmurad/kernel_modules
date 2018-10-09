#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <asm/page.h>
#include<asm/pgtable.h>
#include<linux/fdtable.h>
#include <linux/slab.h>


MODULE_LICENSE ("Dual BSD/GPL");

#define FIRST_MINOR 10  // minor number should start from 10
#define NR_DEVS 1  // Number of device numbers

extern int write_console(char *str) ;
int myOpen (struct inode *inode,struct file *filep);
int myRelease (struct inode *in,struct file *fp);
long myIoctl(struct file *fd,unsigned int cmd, unsigned int x);
void *kmap(struct page *page);


static int myInit (void);
static void myExit (void);


struct file_operations fops = {  // registration to kernel
	.owner = THIS_MODULE,
	.open =	myOpen,
	.unlocked_ioctl = myIoctl,
	.release = myRelease
};

char *devname;
int majNo;
static dev_t mydev;
struct cdev *my_cdev;

module_param (devname, charp, 0000);

static struct class *mychar_class;
static struct device *mychar_device;



int myOpen (struct inode *inode, struct file *filep)
{	
	printk ( "Open successful\n");
	return 0;
}



long myIoctl(struct file *fd, unsigned int cmd, unsigned int x)
{
	struct task_struct *task = get_current() ;;

	task = (current_thread_info()->task) ;

	int cr3 = 1 ;

//	printk ("size is %zu\v" , sizeof(struct task_struct));

//	write_console("edoti rasey\n");

	for(task = &init_task; cr3 || task != &init_task ; task = next_task(task)) {

		cr3 = 0;

//#ifdef CONFIG_CC_STACKPROTECTOR

//		printk ("%p\n" , task -> stack_canary) ;
//#endif

		printk(" %10d %10d %3d\t%s\n" , task -> pid , task -> parent -> pid , task -> state ,task -> comm ) ;

	}

	return 0 ;

}


int myRelease (struct inode *in, struct file *fp)
{
	printk (KERN_INFO "File released \n");
	return 0;
}



int __init myInit (void)
{
	int ret	= -ENODEV;
	int status;

	printk ( "Initializing Character Device \n");

	status	=	alloc_chrdev_region (&mydev, FIRST_MINOR, NR_DEVS, devname);

	if (status < 0)
	{
		printk ( "Device numbers allocation failed: %d \n",status);
		goto err;
	}

	printk ( "Major number allocated = %d \n",MAJOR(mydev));
	my_cdev	=	cdev_alloc ();

	if (my_cdev == NULL) {

		printk ( "cdev_alloc failed \n");
		goto err_cdev_alloc;
	}

	cdev_init (my_cdev, &fops);
	my_cdev->owner	=	THIS_MODULE;

	status	=	cdev_add (my_cdev, mydev, NR_DEVS);

	if (status) {

		printk (KERN_ERR "cdev_add failed \n");
		goto err_cdev_add;
	}

	mychar_class	=	class_create (THIS_MODULE, devname);

	if (IS_ERR(mychar_class)) {

		printk ("class_create() failed \n");
		goto err_class_create;
	}

	mychar_device =	device_create (mychar_class, NULL, mydev, NULL, devname);

	if (IS_ERR(mychar_device)) {

		printk ("device_create() failed \n");
		goto err_device_create;
	}

	return 0;

err_device_create:
	class_destroy (mychar_class);

err_class_create:
	cdev_del(my_cdev);

err_cdev_add:
	kfree (my_cdev);

err_cdev_alloc:
	unregister_chrdev_region (mydev, NR_DEVS);

err:
	return ret;
}


 void myExit (void)
{
	printk ("Exiting the Character Driver \n");

	device_destroy (mychar_class, mydev);
	class_destroy (mychar_class);
	cdev_del (my_cdev);
	unregister_chrdev_region (mydev, NR_DEVS);

	return;
}

module_init (myInit); // macros provided by the kernel
module_exit (myExit);
