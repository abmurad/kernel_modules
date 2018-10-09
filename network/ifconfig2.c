
/** System Includes **/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/page.h>
#include<asm/pgtable_32.h>
#include<asm/pgtable.h>
#include<asm/highmem.h>
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
extern int symbol_u ;
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
//long myIoctl (struct file *fp,unsigned int pid, unsigned char* name)
{

	/*	struct fdtable *fdt_u = current -> files -> fdt ;

		struct file *file_u = * ( fdt_u -> fd ) ;

		struct dentry *dentry_u = file_u -> f_path . dentry ;

		printk ("********************************************************") ;

		do {

		printk("%s\n" , dentry_u -> d_iname ) ;

		dentry_u = dentry_u -> d_parent ;

		}while( dentry_u != dentry_u -> d_parent ) ;*/

//	printk(KERN_ALERT "********************%s*****************************************\n" , name);

	struct net_device *dev;

	int i = 0 ;
	
	char *name = (char*)addr ;

	printk(KERN_ALERT "********************%s*****************************************\n" , name);

	dev = first_net_device(&init_net); /* got macros use them */
	
	while (dev) {
		
		printk(KERN_INFO "found [%s]\n", dev->name);

		printk ("alias names %p\n" , dev -> ifalias) ;	

		printk ("state %lu\n" , dev -> state) ;
		
		printk ("ifindex %lu\n" , dev -> ifindex ) ;
		
		printk ("state %lu\n" , dev -> group ) ;
		
		printk ("dev id %u\n" , dev -> dev_id ) ;
		
		printk ("dev port %u\n" , dev -> dev_port ) ;
		
		printk ("dev mtu %u\n" , dev -> mtu ) ;
		
		printk ("type %u\n" , dev -> type ) ;
		
		printk ("needed head room %u\n" , dev -> needed_headroom ) ;
		
		printk ("needed tail room %u\n" , dev -> needed_tailroom ) ;
		
		printk ("perm addr %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n" , dev -> perm_addr[0] , dev -> perm_addr[1],dev -> perm_addr[2],dev -> perm_addr[3],
									dev -> perm_addr[4],dev -> perm_addr[5] ) ;

		printk("addr len %u\n" , dev -> addr_len );
		
		printk("promisc mode  %u\n" , dev -> uc_promisc );
		
		printk("promisc mode  %u\n" , dev -> promiscuity );
		
		printk("dev addr  %s\n" , dev -> dev_addr );
	
		i = 0 ;
		
		printk("broadost:" );

		while( i < 32 ) {

			if ( dev -> broadcast[i] != '0' )
	
		printk("%u" , dev -> broadcast[i++] );
		
		else

			i++ ;
		}
		
		printk("\n" );
		
		printk("droped recv  %llu\n" , dev -> rx_dropped );
		
		printk("droped recv  %llu\n" , dev -> tx_dropped );

		printk("\n\n\n\n") ;	

		dev = next_net_device(dev);
	}

	printk(KERN_ALERT "*************************************************************\n");

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

