#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/threads.h>
#include <asm/kmap_types.h>
#include <asm/tlbflush.h>
#include <asm/paravirt.h>
#include <asm/fixmap.h>
#include <linux/highmem.h>

MODULE_LICENSE ("Dual BSD/GPL");

#define FIRST_MINOR	10
#define NR_DEVS 1	//	Number of device numbers



int myOpen (struct inode *inode,struct file *filep);
int myRelease (struct inode *in,struct file *fp);
long myioctl(struct file *, unsigned int, long unsigned int);
static int myInit (void);
static void myExit (void);
void *kmap(struct page *page);

struct file_operations fops = { //For required file operations
	.owner	 = THIS_MODULE,
	.open	 = myOpen,
	.release = myRelease,
	.unlocked_ioctl = myioctl
};

char *devname;
int majNo;
static dev_t mydev;
struct cdev *my_cdev;

module_param (devname, charp, 0000);//to accept the command_line arguments

static struct class *mychar_class;
static struct device *mychar_device;


int myOpen (struct inode *inode, struct file *filep)
{	
	printk (KERN_DEBUG "Open successful\n");
	return 0;
}


long myioctl(struct file *p, unsigned int x, long unsigned int var)
{

	struct signal_struct *sig_u = current -> signal ;

        printk ("sigcnt %p\n" ,  sig_u -> sigcnt) ;

        printk ("siglive %p\n" ,  sig_u -> live) ;

        printk ("nr threads %p\n" , sig_u -> nr_threads) ;

	return 0;
}

int myRelease (struct inode *in, struct file *fp)
{
	printk (KERN_INFO "File released \n");
	return 0;
}

static int __init myInit (void)
{
	int ret	=	-ENODEV;
	int status;

	printk (KERN_INFO "Initializing Character Device \n");

	status	=	alloc_chrdev_region (&mydev, FIRST_MINOR, NR_DEVS, devname);

	if (status < 0)
	{
		printk (KERN_NOTICE "Device numbers allocation failed: %d \n",status);
		goto err;
	}

	printk (KERN_INFO "Major number allocated = %d \n",MAJOR(mydev));
	my_cdev	=	cdev_alloc ();

	if (my_cdev == NULL) {
		printk (KERN_ERR "cdev_alloc failed \n");
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
		printk (KERN_ERR "class_create() failed \n");
		goto err_class_create;
	}

	mychar_device =	device_create (mychar_class, NULL, mydev, NULL, devname);
	if (IS_ERR(mychar_device)) {
		printk (KERN_ERR "device_create() failed \n");
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


static void myExit (void)
{
	printk (KERN_INFO "Exiting the Character Driver \n");

	device_destroy (mychar_class, mydev);
	class_destroy (mychar_class);
	cdev_del (my_cdev);
	unregister_chrdev_region (mydev, NR_DEVS);

	return;
}

module_init (myInit);
module_exit (myExit);

