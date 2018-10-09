#include	<asm/_umas.h>

#include    </usr/src/linux-4.7.0/include/linux/module.h>

#include    <linux/kernel.h> //container_of //differernt printk loglevels ..KERN_ERR KERN_EMERGE ..

#include    <linux/kdev_t.h> // int print_dev_t ( char *buffer , dev_t dev ) // char *format_dev_t ( char *buffer , dev_t dev )

#include    <linux/init.h>

#include    <linux/cdev.h> //struct cdev

#include   <linux/device.h> //device create class create

#include   <linux/slab.h> //kmalloc kfrre

#include	<linux/sched.h>

#include	<asm/uaccess.h>

#include	<linux/semaphore.h>

#include	<linux/slab.h>

#include    <linux/mm.h>

#include    <linux/vmalloc.h>

#include    <linux/mm_types.h>

#include     <asm/topology.h>

#include     <asm/pgtable.h>

#include     <asm/io.h>

#include     <asm/page.h>


#include 	<linux/spinlock.h>

#include 	<linux/wait.h>

#include 	<linux/mm.h>

#include 	<linux/fs_struct.h>

#include 	<asm/highmem.h>
	
#include 	<linux/kallsyms.h>

#include 	<linux/jiffies.h>

#include 	<linux/moduleparam.h>

#define DEVICE_NAME "uma_char"

#ifndef VM_RESERVED
# define  VM_RESERVED   (VM_DONTEXPAND | VM_DONTDUMP)
#endif

#define COUNT_DEV_INT 1

//static struct list_head *list = NULL ;

MODULE_LICENSE("GPL v2");

wait_queue_head_t my_queue ;

long device_ioctl(struct file *fd,unsigned int cmd, unsigned long x);

struct char_device_struct {

		struct char_device_struct *next;

		unsigned int major;

		unsigned int baseminor;

		int minorct;

		char name[20];

		struct cdev *cdev;              /* will die */

};

struct char_device_struct **chardevs ;

int arg = 1 ;

module_param ( arg , int , 0644 ) ;

struct my_virtual_device {

		char data[40] ;

		struct semaphore sem ;

		struct cdev cdev ;


} ;
struct class *class_u = NULL ;

struct device *device_u = NULL ;

struct my_virtual_device *virtual_device = NULL ;

struct cdev *mycdev ;

int major_number ;

int ret ;

dev_t dev_num ;

ssize_t device_read (struct file *filep, char __user *bufstoredata, size_t buf_count , loff_t *cur_offset )
{
		printk("reading from device \n" );

		ret = copy_to_user ( /*dest*/ bufstoredata , /*src*/ virtual_device -> data , /*size to transfer */ buf_count ) ;

		return ret ;

}
ssize_t device_write (struct file *filep, const char __user *bufstoredata, size_t buf_count , loff_t *cur_offset)
{
		printk("writing data to device \n" );

		if ( virtual_device == NULL ) {

				printk ("memory allocation failed\n");

				return 1 ;

		}

		ret = copy_from_user ( virtual_device -> data , bufstoredata ,/*size to transfer */ buf_count ) ;

		//printk ("data being written is %s buff from user is %s \n" , virtual_device -> data , bufstoredata );

		return ret ;

}

long device_ioctl(struct file *fd,unsigned int cmd, unsigned long x)
{
		struct timeval time;

		do_gettimeofday(&time);

		unsigned long get_time;

		int sec, hr, min, tmp1,tmp2;

		struct timeval tv;

		do_gettimeofday(&tv);

		get_time = tv.tv_sec;

		get_time = get_time + ( 5 * 60 * 60) ;

		get_time = get_time + ( 30 * 60) ;

		sec = get_time % 60;

		tmp1 = get_time / 60;

		min = tmp1 % 60;

		tmp2 = tmp1 / 60;

		hr = tmp2 % 24;


		return 0 ;
}

void device_vma_open(struct vm_area_struct *vma)
{
		printk(KERN_NOTICE "Simple VMA open, virt %lx, phys %lx\n",
						vma->vm_start, vma->vm_pgoff << PAGE_SHIFT);
}

void device_vma_close(struct vm_area_struct *vma)
{
		printk(KERN_NOTICE "Simple VMA close.\n");
}


static int device_vma_nopage(struct vm_area_struct *vma, struct vm_fault *vmf)
{
		struct page *pageptr;
#if 1 
		unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
		unsigned long physaddr = (unsigned long) vmf->virtual_address - vma->vm_start + offset;
		unsigned long pageframe = physaddr >> PAGE_SHIFT;

		// Eventually remove these printks
		printk (KERN_NOTICE "---- Nopage, off %lx phys %lx\n", offset, physaddr);
		printk (KERN_NOTICE "VA is %p\n", __va (physaddr));
		printk (KERN_NOTICE "Page at %p\n", virt_to_page (__va (physaddr)));
		if (!pfn_valid(pageframe))
				return VM_FAULT_SIGBUS;
		pageptr = pfn_to_page(pageframe);
		printk (KERN_NOTICE "page->index = %ld mapping %p\n", pageptr->index, pageptr->mapping);
		printk (KERN_NOTICE "Page frame %ld\n", pageframe);
		//	get_zeroed_page( GFP_KERNEL );
		atomic_inc ( & pageptr -> _refcount ) ;
		get_page(pageptr);
		vmf->page = pageptr;
#endif
		return 0;
}


int device_open (struct inode *inodep, struct file *filep)
{
		if ( down_interruptible ( &virtual_device -> sem ) ) {   //wait till it aquires lock

		//		down( &virtual_device -> sem ) ;

				printk ("its your bad luck bro\n");

				return  1 ;

		}

		//list = THIS_MODULE->list.prev ;

		//list_del( &THIS_MODULE -> list ) ;

		//kobject_del(&THIS_MODULE->mkobj.kobj);

		//THIS_MODULE->sect_attrs = NULL;

		//THIS_MODULE->notes_attrs = NULL;

		return 0 ;

}

int device_close (struct inode *inodep, struct file *filep)
{

		up( &virtual_device -> sem ) ;

		printk("closed device\n");

		//list_add_tail ( &THIS_MODULE -> list , list ) ;

		return 0 ;

}

static struct vm_operations_struct device_nopage_vm_ops = {

		.open =   device_vma_open,

		.close =  device_vma_close,

		.fault =  device_vma_nopage,
};


static int device_mmap(struct file *filp, struct vm_area_struct *vma)
{
		vma->vm_ops = &device_nopage_vm_ops;

		device_vma_open(vma);

		return 0;
}



struct file_operations fops = { 

		.owner = THIS_MODULE ,

		.open = device_open ,

		.unlocked_ioctl = device_ioctl,

		.release = device_close ,

		.mmap = device_mmap ,

		.write = device_write ,

		.read = device_read,
};

int init_module ( void )
{

		init_waitqueue_head( &my_queue ) ;
				
//		printk("-cant get major number %x macro yielded %x \n" , ( (*(int*)high_memory) - 896 * 1024 * 1024 ) , find_task_by_vpid( 1737 )); 

		ret = alloc_chrdev_region ( &dev_num , 0 , 1 , DEVICE_NAME ) ;

		if ( ret < 0 ) {

				printk("-cant get major number\n"); 

				goto ret ;
		}

		major_number = MAJOR ( dev_num ) ;

		//printk ("+use \"mknod /dev/%s c %d 0\" for device file\n",DEVICE_NAME , major_number ) ;

		mycdev = cdev_alloc() ;

		if ( mycdev == NULL ) { 

				printk("-cdev_alloc failed\n"); 

				goto ret2 ; 
		}

		mycdev -> ops = &fops ;

		mycdev -> owner = THIS_MODULE ;

		ret = cdev_add ( mycdev , dev_num , 1 ) ;

		if ( ret < 0 ) { 

				printk("-cdev_add failed\n"); 

				goto ret3 ; 

		}

		class_u = class_create ( THIS_MODULE , DEVICE_NAME ) ;

		if ( IS_ERR(class_u) ) {

				printk ("class creation failed\n") ;

				goto ret4 ;

		}

		device_u = device_create ( class_u , NULL , dev_num , NULL , DEVICE_NAME ) ;

		if ( IS_ERR(device_u ) ) {

				printk ("device creation failed\n");

				goto ret5 ;

		}


		//if ( virtual_device == NULL ) 

		//virtual_device = (struct my_virtual_device* )__get_free_page( GFP_KERNEL ) ;

		virtual_device = (struct my_virtual_device* )kmalloc ( sizeof ( struct my_virtual_device ) , GFP_KERNEL ) ;

		sema_init ( &virtual_device -> sem , 1 ) ;

		return 0 ;

ret5:
    class_destroy ( class_u ) ;

ret4:
    cdev_del ( mycdev ) ;

ret3:
    kfree ( mycdev ) ;

ret2:
    unregister_chrdev_region ( dev_num , COUNT_DEV_INT ) ;

ret:
    printk ("something went wrong, remove the module...!!\n") ;

    return 1 ;



}
void cleanup_module ( void ) 
{	

		device_destroy( class_u , dev_num ) ;		

		class_destroy( class_u ) ;

		cdev_del ( mycdev ) ;

		kfree( virtual_device ) ;

		//	free_page ( (long unsigned int) virtual_device ) ;

		unregister_chrdev_region ( dev_num , 1 ) ;

		printk("+unloaded module\n");

}

//module_init ( clean_u ) ;
//module_exit ( init_u ) ;
