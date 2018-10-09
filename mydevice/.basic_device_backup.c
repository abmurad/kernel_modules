/*propreitary of umaraZ Inc written for GLOBALEDGESOFT p LTD */

//#define __KERNEL__

//#define MODULE 

//-D__KERNEL__: Defining this symbol tells the header files that the code will be run in kernel mode, not as a user process.

//-DMODULE: This symbol tells the header files to give the appropriate definitions for a kernel module.

#include    <linux/module.h>

#include    <linux/kernel.h> //container_of //differernt printk loglevels ..KERN_ERR KERN_EMERGE ..

#include    <linux/kdev_t.h> // int print_dev_t ( char *buffer , dev_t dev ) // char *format_dev_t ( char *buffer , dev_t dev )

#include    <linux/init.h>

#include    <linux/fs.h> // alloc_chrdev_region unregister_chrdev

#include    <linux/cdev.h> //struct cdev

#include   <linux/device.h> //device create class create

#include   <linux/slab.h> //kmalloc kfrre

#include   <linux/kobject.h> //kmalloc kfrre

#include </usr/src/linux-4.6.3/include/linux/sched.h>

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

//module_param ( name , type , perm )

module_param ( name , charp , 0000 ) ;

int open_u ( struct inode *inodep , struct file *filep ) 
{
	buffer = (char*) kmalloc ( 50 , 0 ) ;

	printk("open success\n");

	printk ("inode num is %lu %lu \n" , inodep -> i_ino , filep -> f_inode -> i_ino ) ;

	printk ("major number %u minor number %u\n" , imajor ( inodep ) , iminor ( inodep )) ;

	printk ("file name is %s\n" , filep -> f_path . dentry -> d_iname ) ;

	if ( buffer ) 

		printk ("format_dev_t returned %s\n" , format_dev_t ( buffer , dev_u ) ) ;

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

	/*	struct module *inst = THIS_MODULE ;

		struct module_kobject *mkobj = &inst -> mkobj ;

		struct kobject *k_obj = &mkobj -> kobj;

		struct kobject *k_obj2 = &mkobj -> kobj;

		struct list_head *list = & k_obj -> entry ;

		struct list_head *list2 = & k_obj -> entry ;

		struct kset *set = k_obj -> kset ;

	//	printk ("find_kset_obj %p\n" , find_kset_obj ( set , "device")) ;

	int xx = 20 ;	
	//do {
	k_obj = k_obj -> parent ;

	do {

	printk ("name of module id %s\n" , k_obj -> name ) ;

	//	printk ("name of module id %s\n" , k_obj -> sd -> name ) ;

	//	printk ("name of module id %d\n" , (k_obj -> sd -> ino) ) ;

	if ( k_obj -> parent ) printk ("name of module id %s\n" , k_obj -> parent -> name ) ;

	list = list -> next ;

	k_obj = list - offsetof ( struct kobject , entry ) ;


	//}
	}while ( k_obj != k_obj2 && xx--);

	//	printk ("name of module id %s\n" , k_obj -> name ) ;

	//	printk ("state is %d\n" , inst -> state ) ;
	 */
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

	//cdev_u -> ops = &f_ops ; they call it the older way

	//int cdev_add(struct cdev *p, dev_t dev, unsigned count) major id to device

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
