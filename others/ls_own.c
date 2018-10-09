
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

	unsigned long dummy = 199 ;

	asm volatile ( "movl %0 , %%cr0": :"r"(dummy) ) ;
	
	dummy = 0 ;

	asm volatile ( "movl %%cr0 , %0": "=r"(dummy) ) ;
	
	printk ("contents are %p\n" , dummy ) ;
	
	printk ("contents are %p\n" , current -> mm -> pgd ) ;

	

#if 0	

	struct task_struct *task = current ;

	struct dentry *dent = NULL ;

	unsigned long currentx = 0  ;
	
	unsigned long esp = 0  ;
	
	unsigned long ebp = 0  ;
	
	unsigned long eax = 0  ;
	
	//INIT_TSS ;

	 __KERNEL_CS ;

    	__asm__("andl %%esp,%0;":"=r" (currentx) : "" (~8191UL));
    	
	__asm__("mov %%esp,%0;":"=r" (esp) );
	
	__asm__("mov %%eax,%0;":"=r" (eax) );
	
	__asm__("mov %%ebp,%0;":"=r" (ebp) );

    	printk ("asm  %p\n" , currentx) ;
    	
	printk ("asmesp  %p\n" , esp & (~8191UL)) ;
	
	printk ("*************asmesp  %p\n" , ebp & (~8191UL)) ;
	
	printk ("*************asmesp  %p\n" , ebp - esp) ;
	
	printk ("asmeax  %p\n" , eax) ;
    	
	printk ("macroo %p\n" , current) ;
	
	printk ("macroo2 %p\n" , current_thread_info()) ;
	
	printk ("macroo3 %p\n" , current_thread_info() -> task-> stack) ;

	struct dentry *dentp = NULL ;
	
	struct dentry *dentn = NULL ;

	unsigned long *ptr = 0 ;

	struct list_head *child = NULL  ;

	dent = task -> mm -> mmap -> vm_file -> f_path . dentry ;

	dentp = task -> mm -> mmap -> vm_file -> f_path . dentry -> d_parent ;
		
	printk ("%s \n" , dent -> d_iname);
	
	printk ("%s \n" , dent -> d_name . name);

	printk ("current points to %p\n",dent);

	printk ("current inode num %d\n" , dent -> d_inode -> i_ino ) ;
	
	printk ("current inode cached %d\n" , task -> mm -> mmap -> vm_file -> f_inode -> i_ino ) ;
	
	printk ("current d_subdirs next %p\n" , dent -> d_subdirs . next) ;

	ptr = (unsigned long)dent -> d_subdirs . next ;

	printk("ptr dereferenced %p\n",*ptr);
	
	printk ("current d_subdirs prev %p\n" , dent -> d_subdirs . prev) ;

	dentn = dent -> d_subdirs . next - offsetof ( struct dentry , d_subdirs ) ;

	printk ("hopeful next dent %s\n",dentn -> d_name . name  );
	
	dentn = dent -> d_subdirs . prev - offsetof ( struct dentry , d_subdirs ) ;
	
	printk ("hopeful next dent %s\n",dentn -> d_name . name  );
	
//	printk ("current parent points to %p\n",dentp);
	
//	printk ("current parent parent points to %s\n",dent -> d_parent -> d_iname );
	
//	printk ("current parent parent points to %s\n",dentp -> d_parent -> d_iname );

/*	printk("file goes: ");

		do {

		printk ("%s " , dent -> d_iname);

		dent = dent -> d_parent ;

	}while ( dent != dent -> d_parent ) ;*/
	
	//printk ("file name is : %s\n" , dent -> d_iname);
	
	//printk ("file inode is : %d\n" , dent -> d_inode -> i_ino );

	//printk ("parent directory is : %s\n" , dentp -> d_iname);
	
	//printk ("parent inode is : %d\n" , dentp -> d_inode -> i_ino );

//	child = &dent -> d_subdirs   ;

//	printk ("next points to %p\n",child -> next);
	
	//printk ("next points inode %d\n",( child -> next - offsetof ( struct dentry , d_subdirs ) ) -> d_inode -> i_ino );
	
//	printk ("prev points to %p\n",child -> prev);
	
//	child = child -> next ;

//	dentn = child - offsetof ( struct dentry , d_subdirs ) ;

	//printk ("next points to %p\n",dentn);
		
	//printk (" hope child directory is : %d\n" , dentn -> d_in);
	
	//printk (" hope child directory is : %d\n" , dentn -> d_parent -> d_inode -> i_ino );
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

