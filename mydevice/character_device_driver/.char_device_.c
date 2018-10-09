// /sys/module/read_write/parameters

#include    </usr/src/linux-4.7.0/include/linux/module.h>

#include    <linux/kernel.h> //container_of //differernt printk loglevels ..KERN_ERR KERN_EMERGE ..

#include    <linux/kdev_t.h> // int print_dev_t ( char *buffer , dev_t dev ) // char *format_dev_t ( char *buffer , dev_t dev )

#include    <linux/init.h>

#include    <linux/cdev.h> //struct cdev

#include   <linux/device.h> //device create class create

#include   <linux/slab.h> //kmalloc kfrre

#include <linux/sched.h>

#include <asm/uaccess.h>

#include <linux/semaphore.h>

#include        <linux/slab.h>

#include        <linux/mm.h>

#include        <linux/vmalloc.h>

#include        <linux/mm_types.h>

#include        <asm/topology.h>

#include        <asm/pgtable.h>

#include        <asm/io.h>

#include        <asm/page.h>


#include <linux/spinlock.h>

#include <linux/wait.h>

#include <linux/mm.h>

#include <asm/highmem.h>

#include <linux/kallsyms.h>

#include <linux/jiffies.h>

#include <linux/moduleparam.h>

#define DEVICE_NAME "uma_char"

#ifndef VM_RESERVED
# define  VM_RESERVED   (VM_DONTEXPAND | VM_DONTDUMP)
#endif


MODULE_LICENSE("GPL");

wait_queue_head_t my_queue ;

long device_ioctl(struct file *fd,unsigned int cmd, unsigned long x);

struct char_device_struct {

	struct char_device_struct *next;

	unsigned int major;

	unsigned int baseminor;

	int minorct;

	char name[64];

	struct cdev *cdev;              /* will die */

};

struct char_device_struct **chardevs ;

int arg = 1 ;

module_param ( arg , int , 0644 ) ;

struct my_virtual_device {

	char data[300] ;

	struct semaphore sem ;

	struct cdev cdev ;


} ;

struct my_virtual_device *virtual_device = NULL ;

struct cdev *mycdev ;

int major_number ;

int ret ;

dev_t dev_num ;

/**/

struct dentry  *file;

struct mmap_info
{
    char *data;
    int reference;
};

void mmap_open(struct vm_area_struct *vma)
{
    struct mmap_info *info = (struct mmap_info *)vma->vm_private_data;
    info->reference++;
}

void mmap_close(struct vm_area_struct *vma)
{
    struct mmap_info *info = (struct mmap_info *)vma->vm_private_data;
    info->reference--;
}

static int mmap_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
    struct page *page;
    struct mmap_info *info;

    info = (struct mmap_info *)vma->vm_private_data;
    if (!info->data)
    {
        printk("No data\n");
        return 0;
    }

    page = virt_to_page(info->data);

    get_page(page);
    vmf->page = page;

    return 0;
}

struct vm_operations_struct mmap_vm_ops =
{
    .open =     mmap_open,
    .close =    mmap_close,
    .fault =    mmap_fault,
};

int device_mmap(struct file *filp, struct vm_area_struct *vma)
{
    vma->vm_ops = &mmap_vm_ops;

    vma->vm_flags |= VM_RESERVED;

    vma->vm_private_data = filp->private_data;

    mmap_open(vma);

    return 0;
}


/**/

ssize_t device_read (struct file *filep, char __user *bufstoredata, size_t buf_count , loff_t *cur_offset )
{
	printk("reading from device\n");

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

int device_open (struct inode *inodep, struct file *filep)
{
	if ( down_interruptible ( &virtual_device -> sem ) ) {   //wait till it aquires lock

		printk ("its your bad luck bro\n");

		return  1 ;

	}
	return 0 ;

}
#if 0
int device_mmap ( struct file *filp , struct vm_area_struct *vma ) 
{
	printk ("mmap calle successful\n");

	#if 0

	if ( remap_pfn_range ( vma , vma -> vm_start , ( ( func( &virtual_device ) ) << vma -> vm_pgoff)  , 8191 , vma -> vm_page_prot ) ) {


		printk("remap_pfn_range has failed\n");

		return 1 ;

	}

	#endif
#if 0
	vma -> vm_ops = &device_vm_ops ;

	vma -> vm_flags |= VM_RESERVED ;

	device_vma_open(vma);
#endif
	return 0 ;

}
#endif

#if 0
void device_vma_open (struct vm_area_struct *vma ) {

	printk("vma open\n");

	return 0 ;

}
void device_vma_close (struct vm_area_struct *vma ) {

        printk("vma open\n");

        return 0 ;

}

#endif

int device_close (struct inode *inodep, struct file *filep)
{

	up( &virtual_device -> sem ) ;

	printk("closed device\n");

	return 0 ;

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

	ret = alloc_chrdev_region ( &dev_num , 0 , 1 , DEVICE_NAME ) ;

	if ( ret < 0 ) {

		printk("-cant get major number\n"); 

		return 0 ;
	}

	major_number = MAJOR ( dev_num ) ;

	printk ("+use \"mknod /dev/%s c %d 0\" for device file\n",DEVICE_NAME , major_number ) ;

	mycdev = cdev_alloc() ;

	if ( mycdev == NULL ) { 

		printk("-cdev_alloc failed\n"); 

		return  0 ; 
	}

	mycdev -> ops = &fops ;

	mycdev -> owner = THIS_MODULE ;

	ret = cdev_add ( mycdev , dev_num , 1 ) ;

	if ( ret < 0 ) { 

		printk("-cdev_add failed\n"); 

		return 0 ; 

	}

	if ( virtual_device == NULL ) 

	virtual_device = (struct my_virtual_device* )__get_free_page( GFP_KERNEL ) ;

	sema_init ( &virtual_device -> sem , 1 ) ;

	return 0 ;

}
void cleanup_module ( void ) 
{	
	cdev_del ( mycdev ) ;

	free_page ( (long unsigned int) virtual_device ) ;

	unregister_chrdev_region ( dev_num , 1 ) ;

	printk("+unloaded module\n");

}

//module_init ( clean_u ) ;
//module_exit ( init_u ) ;
