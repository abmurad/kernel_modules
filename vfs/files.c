
/** System Includes **/
#include <linux/init.h>
#include <linux/genhd.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>
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

	struct fdtable *fdt_u = current -> files -> fdt ;

	struct file *file_u = * ( fdt_u -> fd ) ;

	struct inode *inode_u = file_u -> f_inode ;

	struct super_block *sb = inode_u -> i_sb ;

	struct super_block *sb_temp = inode_u -> i_sb ;

	struct dentry *dentry_u = file_u -> f_path . dentry ;

	struct dentry *dentry_temp = file_u -> f_path . dentry ;

	struct file_system_type *type_u = sb -> s_type ;

	struct list_head *list = &sb -> s_list ;

	struct list_head *list2 = NULL ;

	struct block_device *b_dev = sb -> s_bdev ;
	
	struct block_device *b_devt = sb -> s_bdev ;
	
	struct list_head *bdlist = NULL ;

	struct list_head *bdlist2 = NULL ;
				
	printk("\n\n");

	do {

/*		if ( sb -> s_type && sb -> s_type -> name ) {

			if ( ! strncmp ( "ext4" , sb -> s_type -> name , 4 ) ) {

				b_dev = b_devt = sb -> s_bdev ;
	
				bdlist = bdlist2 = &b_dev -> bd_list ;
			
				do{

				printk ("smajor of block %d\n" , MAJOR(b_dev -> bd_dev) ) ;
				
				printk ("sminor of block %d\n" , MINOR(b_dev -> bd_dev) ) ;
				
				if ( (b_dev -> bd_disk) )
				printk ("name of driver block %s\n" , (b_dev -> bd_disk -> disk_name) ) ;

				//printk("inode number is %lu\n",b_dev -> bd_inode -> i_ino );

				if ( b_dev -> bd_contains ) {
			
					printk("contains %d major\n" , MAJOR( b_dev -> bd_contains -> bd_dev ) );
					
					printk("contains %d minor\n" , MAJOR( b_dev -> bd_contains -> bd_dev ) );

				}

				bdlist = bdlist -> next ;
	
				b_dev = bdlist -> next - offsetof ( struct block_device , bd_list ) ;

				}while ( bdlist != bdlist2 );
		
				printk("\n\n");

				break ;

			}

		}*/

		if ( sb -> s_type ) 
		printk("name: %s\n" , sb -> s_type -> name );

		  //printk ("index %u\n" , sb -> s_dev ) ;

		if (sb->s_subtype)
		printk ("sutype %p\n" , sb -> s_subtype ) ;

		printk ("block size %u\n" , sb -> s_blocksize ) ;

		printk ("max bytes %u\n" , sb -> s_maxbytes ) ;

		printk ("magic bytes %u\n" , sb -> s_magic ) ;

		printk ("some name %p\n" , sb -> s_root -> d_iname ) ;

		if ( sb -> s_bdev )

		printk ("smajor of block %d\n" , MAJOR(sb -> s_bdev -> bd_dev) ) ;

		/*	offsetof ( struct dentry , d_subdirs ) ;

			dentry_temp = (dentry_u -> d_subdirs . next ) - offsetof ( struct dentry , d_subdirs ) ;

			printk ("kill %s\n" , dentry_temp -> d_iname ) ;

			printk ("some name %s\n" , sb -> s_root -> d_sb -> s_root -> d_iname ) ;*/

		list = list -> next ;

		sb = list - offsetof ( struct super_block , s_list ) ;

		printk("\n\n");

	}while ( sb != sb_temp ) ;

	printk ("********************************************************\n") ;




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

