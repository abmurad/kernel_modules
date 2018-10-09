// /sys/module/read_write/parameters

#include    </usr/src/linux-4.7.0/include/linux/module.h>

#include    <linux/kernel.h> //container_of //differernt printk loglevels ..KERN_ERR KERN_EMERGE ..

#include    <linux/kdev_t.h> // int print_dev_t ( char *buffer , dev_t dev ) // char *format_dev_t ( char *buffer , dev_t dev )

#include    <linux/init.h>

#include    <linux/fs.h> // alloc_chrdev_region unregister_chrdev

#include    <linux/cdev.h> //struct cdev

#include   <linux/device.h> //device create class create

#include   <linux/slab.h> //kmalloc kfrre

#include <linux/sched.h>

#include <asm/uaccess.h>

#include <linux/semaphore.h>

#include <linux/spinlock.h>

#include <linux/wait.h>

#include <linux/jiffies.h>

#include <linux/moduleparam.h>

#define DEVICE_NAME "uma_char"

MODULE_LICENSE("GPL");

static int x = 0  ;

//wait_queue_head_t queue_u ;

module_param( x , int ,  0644 ) ;

//module_param (devname, charp, 0000);

MODULE_PARM_DESC( x , "life is easy" );

struct fake_device {

	char data[100] ;

//	struct semaphore sem ;

	spinlock_t spin ;

} virtual_device ;

struct cdev *mycdev ;

int major_number ;

int ret ;

dev_t dev_num ;

ssize_t device_read (struct file *filep, char __user *bufstoredata, size_t buf_count , loff_t *cur_offset )
{
	printk("reading from device\n");

//	wait_event_interruptible ( queue_u , x==100 ) ;
	
	printk ("access_ok returned %ld\n" , access_ok ( VERIFY_WRITE  , bufstoredata, buf_count ) );

	ret = copy_to_user ( /*dest*/ bufstoredata , /*src*/ virtual_device.data , /*size to transfer */ buf_count ) ;

	return ret ;

}
ssize_t device_write (struct file *filep, const char __user *bufstoredata, size_t buf_count , loff_t *cur_offset)
{
	printk("writing data to device\n");

//	wake_up_interruptible( &queue_u ) ;
	
	printk ("access_ok returned %ld\n" , access_ok ( VERIFY_WRITE  , bufstoredata, buf_count ) );

	ret = copy_from_user ( virtual_device.data , bufstoredata ,/*size to transfer */ buf_count ) ;

	return ret ;

}

int device_open (struct inode *inodep, struct file *filep)
{
	/*if ( down_interruptible ( &virtual_device . sem ) ) {   //wait till it aquires lock

		printk ("its your bad luck bro\n");

		return  1 ;

	}*/

	//spin_lockirqsave (  &virtual_device . spin , ulong flags ) ; previous interrupt state returned into flags
	
	//spin_lockirq (  &virtual_device . spin ) ; 

	//spin_lock_bh ( &virtual_device . spin ) ;

//	spin_lock_interruptible (  &virtual_device . spin ) ;

	return 0 ;

}

int device_close (struct inode *inodep, struct file *filep)
{
	spin_unlock (  &virtual_device . spin ) ;
	
	//spin_unlock_irqstore (  &virtual_device . spin , ulflags ) ;
	
	//spin_unlock_irq (  &virtual_device . spin , ulflags ) ;
	
	//spin_unlock_bh (  &virtual_device . spin , ulflags ) ;

	printk("closed device\n");

	return 0 ;

}

struct file_operations fops = { 

	.owner = THIS_MODULE ,

	.open = device_open ,

	.release = device_close ,

	.write = device_write ,

	.read = device_read,
};

//static int __init init_u ( void )
int init_module ( void )
{
	ret = alloc_chrdev_region ( &dev_num , 0 , 1 , DEVICE_NAME ) ;
	//static inline int register_chrdev(unsigned int major, const char *name,         
	//                const struct file_operations *fops)     

	//ret = register_chrdev(249, "uma_char", &fops);

	if ( ret < 0 ) {

		printk("killed\n"); 

		return 0 ;
	}

	major_number = MAJOR ( dev_num ) ;

	printk ("use \"mknod /dev/%s c %d 0\" for device file\n",DEVICE_NAME , major_number ) ;
	
	printk("jiffies %lu" , jiffies);
	
	printk("1 second in the future %lu" , jiffies + HZ);
	
	printk("half seconds %lu" , jiffies + HZ/2 );
	
	//printk("cpuinfo %p" , cpuinfo );
	
	//printk("n milliseconds %lu" , jiffies + n * HZ/2 );

	mycdev = cdev_alloc() ;

	if ( mycdev == NULL ) { 

		printk("killed again\n"); 

		return  0 ; 
	}

	mycdev -> ops = &fops ;

	mycdev -> owner = THIS_MODULE ;

	ret = cdev_add ( mycdev , dev_num , 1 ) ;

	if ( ret < 0 ) { 

		printk("killed again and again\n"); 

		return 0 ; 

	}

//	sema_init ( &virtual_device . sem , 1 ) ;

	spin_lock_init ( &virtual_device . spin ) ;

	//init_waitqueue_head ( &queue_u ) ;

	return 0 ;
	
}
//static void __exit clean_u ( void ) 
void cleanup_module ( void ) 
{	
	cdev_del ( mycdev ) ;

	unregister_chrdev_region ( dev_num , 1 ) ;
//	unregister_chrdev ( major_number , DEVICE_NAME ) ;

	printk("unloades module\n");

}

//module_init ( clean_u ) ;
//module_exit ( init_u ) ;
