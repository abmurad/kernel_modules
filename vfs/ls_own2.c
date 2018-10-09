
/** System Includes **/
#include <linux/init.h>
#include <linux/path.h>
#include <linux/mount.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/page.h>
#include<asm/pgtable.h>
#include<linux/fdtable.h>

#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/posix_types.h>
#include <linux/compiler.h>
#include <linux/spinlock.h>
#include <linux/rcupdate.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/fs.h>

#include <linux/netdevice.h>
#include <linux/atomic.h>
#include <linux/slab.h>

#include<linux/fs.h>
MODULE_LICENSE ("Dual BSD/GPL");

/** Constants **/
#define FIRST_MINOR	10
#define NR_DEVS 1	//	Number of device numbers

// Function Declaration for syscall definitions
int myOpen (struct inode *inode,struct file *filep);
int myRelease (struct inode *in,struct file *fp);
long myIoctl (struct file *fp,unsigned int pid,unsigned long addr);
//long myIoctl (struct file *fp,unsigned int pid,unsigned char* name);

//Initialization routines
static int myInit (void);
static void myExit (void);

struct file_operations fops = {
	.owner	        =	THIS_MODULE,
	.open	        =	myOpen,
	.unlocked_ioctl =   	myIoctl,
	.release	=    	myRelease,
};
/* Global varibales */
char *devname; // Contains device name
int majNo;
static dev_t mydev; // encodes major number and minor number
struct cdev *my_cdev; // holds character device driver descriptor

/* To accept input from the command line */
module_param (devname, charp, 0000);

// Class and device structures 
static struct class *mychar_class;
static struct device *mychar_device;

/*
 * myopen: open fucntions of the pseudo driver
 *
 */

int myOpen (struct inode *inode, struct file *filep)
{	
	printk (KERN_INFO "Open successful\n");


	return 0;
}

/*
 * myRelease: close function of the pseduo driver
 *
 */

int myRelease (struct inode *in, struct file *fp)
{
	printk (KERN_INFO "File released \n");
	return 0;
}

/*
 * myIoctl: function for doing control operations on driver
 *
 */

long myIoctl (struct file *fp,unsigned int pid, unsigned long addr)
{


	printk ("****************%d****************\n\n\n\n" , pid );;

	struct task_struct *task = current ;

	struct dentry *dent = NULL ;

	struct dentry *dentp = NULL ;

	struct dentry *dentn = NULL ;
	
	struct dentry *dentv = NULL ;

	unsigned long *ptr = 0 ;

	struct file *file_u = NULL ;
	
	struct fdtable *fd_u = NULL ;

	struct super_block *sb = NULL ;

	struct super_block *sb2 = NULL ;

	struct list_head *child = NULL  ;

	struct list_head *child2 = NULL  ;
	
	int index  = 5 ;

	fd_u =  (task -> files -> fdt ) ;

	file_u = * ( fd_u -> fd ) ;

//	dentv = file_u -> f_path . mnt -> mnt_root  ;
	
//	child = &dentv -> d_subdirs ;

	dentv = file_u -> f_path . dentry  ;

	child = &dentv -> d_subdirs ;
	
	//dentt = file_u -> f_path . dentry  ;

	//child = &task -> mm -> mmap -> vm_file -> f_path . dentry -> d_parent -> d_subdirs ;

	//dentp = task -> mm -> mmap -> vm_file -> f_path . dentry -> d_parent ;

	do {
	
//	printk("***1 name is %s\n", dentv -> d_name . name);
	
	printk("2 d_sb is  %p\n", dentv -> d_sb );
	
	printk("2 d_sb is  %s\n", dentv -> d_sb -> s_root ->  d_name . name );

	child = child -> next  ;
	
	dentv = ( char* ) child -> next   - ( offsetof ( struct dentry , d_subdirs ) ) ;

	}while ( index -- ) ;
	
//	printk("1 name is %s\n", dentv -> d_name . name);
	
//	printk("2 name is %s\n", dentv -> d_iname);
	
#if 0
	//sb = sb2 = dent -> d_sb ;

	//dent = sb -> s_root ;

	//dentp = dent -> d_parent ;

	//do {

	printk("name is %s\n",dent -> d_name . name);

	printk("name is %s\n",dent -> d_iname);

	//printk("pname is %s\n",dentp -> d_name . name);

	//	printk("pname is %s\n",dentp -> d_iname);

	dentp = ( dentp -> d_child . next ) - ( offsetof ( struct dentry , d_child ) ) ;

	printk("name is %s\n",dentp -> d_name . name);

	printk("name is %s\n",dentp -> d_iname);

	//dent = ( dent -> d_child . prev ) - ( offsetof ( struct dentry , d_child ) ) ;

	printk("name is %s\n",dent -> d_name . name);

	printk("name is %s\n",dent -> d_iname);

	//}while(); 

	dentp = dent -> d_parent ;

	child = & dentp -> d_subdirs ;

	//	do{

	while ( child -> next != child2 ) {

		dent = child -> next - offsetof ( struct dentry , d_subdirs );

		/*printk ("child2 %p\n", child2 );

		  printk("current child is %p\n", child);

		  printk ("next is %p\n", child -> next);

		  printk ("prev is %p\n", child -> prev);*/

		printk("name is %s\n" , dent ->d_name .name);

		printk("name is %s\n" , dent ->d_iname);

		printk("\n\n\n");

		child = child  ->  next ;

	}

	//	}while ( child -> next != child2 );

#endif

	printk ("\n\n\n************************************************");

	return 0;
}

/*
 * myInit: init function of the kernal module
 *
 */

static int __init myInit (void)
{
	int ret	=	-ENODEV;
	int status;

	printk (KERN_INFO "Initializing Character Device \n");

	// Allocating Device Numbers
	status	=	alloc_chrdev_region (&mydev, FIRST_MINOR, NR_DEVS, devname);
	if (status < 0)
	{
		printk (KERN_NOTICE "Device numbers allocation failed: %d \n",status);
		goto err;
	}

	printk (KERN_INFO "Major number allocated = %d \n",MAJOR(mydev));
	my_cdev	=	cdev_alloc (); // Allocate memory for my_cdev
	if (my_cdev == NULL) {
		printk (KERN_ERR "cdev_alloc failed \n");
		goto err_cdev_alloc;
	}

	cdev_init (my_cdev, &fops); // Initialize my_cdev with fops
	my_cdev->owner	=	THIS_MODULE;

	status	=	cdev_add (my_cdev, mydev, NR_DEVS); // Add my_cdev to the list
	if (status) {
		printk (KERN_ERR "cdev_add failed \n");
		goto err_cdev_add;
	}
	// Create a class an entry in sysfs
	mychar_class = class_create (THIS_MODULE, devname);
	if (IS_ERR(mychar_class)) {
		printk (KERN_ERR "class_create() failed \n");
		goto err_class_create;
	}
	// Creates mychar_device in sysfs and an
	// device entry wiil be made in /dev directory
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
/*
 * myExit: cleanup function of the kernal module
 */

static void myExit (void)
{
	printk (KERN_INFO "Exiting the Character Driver \n");

	device_destroy (mychar_class, mydev);
	class_destroy (mychar_class);
	cdev_del (my_cdev);
	unregister_chrdev_region (mydev, NR_DEVS);

	return;
}

module_init(myInit);
module_exit(myExit);

