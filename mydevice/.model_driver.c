/*propreitary of umaraZ Inc written for GLOBALEDGESOFT p LTD */

#include    <linux/module.h>

#include    <linux/kernel.h> //container_of //differernt printk loglevels ..KERN_ERR KERN_EMERGE ..

#include    <linux/kdev_t.h> // int print_dev_t ( char *buffer , dev_t dev ) // char *format_dev_t ( char *buffer , dev_t dev )

#include    <linux/init.h>

#include    <linux/fs.h> // alloc_chrdev_region unregister_chrdev

#include    <linux/cdev.h> //struct cdev

#include   <linux/device.h> //device create class create

#include   <linux/slab.h> //kmalloc kfrre

#include   <linux/kobject.h> //kmalloc kfrre

#include </usr/src/linux-4.6.2/include/linux/sched.h>

dev_t dev_u ;

int flag = 0 ;

char *buffer  = NULL ;

struct file_operations f_ops;

struct class *class_u = NULL ;

struct device *device_u = NULL ;

struct cdev *cdev_u  = NULL ; // this struct kernel uses internally to rep char devices 

extern struct kobject *kset_find_obj(struct kset *kset, const char *name) ;

#define BASE_MINOR 22

#define COUNT_DEV_INT 1

char *name = NULL ;


module_param ( name , charp , 0000 ) ;

int open_u ( struct inode *inodep , struct file *filep ) 
{
	printk("open success\n");

	return 0 ;
}

int release_u (struct inode *inodep , struct file *filep )
{
	printk("release success\n");

	return 0 ;
}

long ioctl_u ( struct file *filep, unsigned int x , unsigned long some )
{

	printk("ioctl success\n");

	return 0 ;

}

static int __init device_init_module ( void )
{

	int status = 0 ;

	if ( name == NULL ) {

		printk ("you need to provide device name\n") ;

		goto ret ;
	}

	status = alloc_chrdev_region ( &dev_u, BASE_MINOR, COUNT_DEV_INT, name ) ;

	if ( status < 0 ) {

		printk ("major num allocation failed\n") ;

		goto ret ;

	}

	cdev_u = cdev_alloc ( ) ;

	if ( cdev_u == NULL ) {

		printk ("low on memory\n") ;

		goto ret2 ;

	}

	{

		f_ops . owner = THIS_MODULE ;

		f_ops . open = open_u ;

		f_ops . release = release_u ;

		f_ops . unlocked_ioctl = ioctl_u ;

	}

	cdev_u -> owner = THIS_MODULE ;

	cdev_init ( cdev_u , &f_ops ) ;

	status = cdev_add ( cdev_u , dev_u , COUNT_DEV_INT ) ;

	if ( status ) {

		printk ("cdev_add failed\n");

		goto ret3;

	}

	class_u = class_create ( THIS_MODULE , name ) ;

	if ( IS_ERR(class_u) ) {

		printk ("class creation failed\n") ;

		goto ret4 ;

	}

	device_u = device_create ( class_u , NULL , dev_u , NULL , name ) ;

	if ( IS_ERR(device_u ) ) {

		printk ("device creation failed\n");

		goto ret5 ;

	}

	flag = 1 ;

	return 0 ;

ret5:
	class_destroy ( class_u ) ;

ret4:
	cdev_del ( cdev_u ) ;

ret3:
	kfree ( cdev_u ) ;

ret2:
	unregister_chrdev_region ( dev_u , COUNT_DEV_INT ) ;

ret:
	printk ("something went wrong, remove the module...!!\n") ;

	return 1 ;

}

static void __exit device_cleanup_module ( void )

{
	if ( flag ) {

		device_destroy ( class_u , dev_u ) ;

		class_destroy ( class_u );

		cdev_del ( cdev_u ) ;

		kfree(cdev_u) ;

		unregister_chrdev_region ( dev_u , COUNT_DEV_INT ) ;

		kfree( buffer ) ;

	}

	printk ("module unloaded successfully..!!") ;

	return ;

}

MODULE_AUTHOR("saraboju umaraju charY");

MODULE_DESCRIPTION ("learning to define device behaviour");

module_exit ( device_cleanup_module ) ;

module_init ( device_init_module ) ;

MODULE_LICENSE("GPL v2");

/******************* END OF DEVICE DRIVER ****************/
