/*property of umaraZ Inc written for GLOBALEDGESOFT p LTD */

//#include	<asm/_umas.h> /* well this is of not much imp now */

#include    <linux/module.h>

#include    <linux/kernel.h> //container_of //differernt printk loglevels ..KERN_ERR KERN_EMERGE ..

#include    <linux/kdev_t.h> // int print_dev_t ( char *buffer , dev_t dev ) // char *format_dev_t ( char *buffer , dev_t dev )

#include    <linux/init.h>

#include    <linux/genhd.h>

#include    <linux/bio.h>

#include    <linux/blkdev.h>

#include   <linux/slab.h> //kmalloc kfrre

#include   <linux/kallsyms.h>

#include   <linux/spinlock.h>

#include   <linux/moduleparam.h>

#define DEVICE_NAME "disk_local"

#define GET_NAME 2147768832 

#define WRITE_LOCAL 1

#define KERNEL_SECTOR_SIZE 512

int major_number ;

int flag = 1 ;

int ret ;

dev_t dev_num ;

void my_request ( struct request_queue *q );

int device_open (struct block_device *, fmode_t);

void device_close (struct gendisk *, fmode_t);

int device_ioctl (struct block_device *, fmode_t, unsigned, unsigned long);

struct blk_dev {

	int size ;

	spinlock_t lock;

	char *data ;

	struct request_queue *queue ;

	struct gendisk *gdisk ;

};

struct blk_dev *my_inst ;

void blk_operations ( struct blk_dev *dev , unsigned long sector , unsigned long nsect , char *buffer , int operation ) 
{
	unsigned long offset = sector * 512 ;

	unsigned long nbytes = nsect * 512 ;

	/* a little validation  */

	if ( ( offset + nbytes ) > dev -> size ) {

		printk("-requesting more data than size of virtual disk\n");

		return ;

	}

	if ( operation == WRITE_LOCAL ) 

		memcpy(dev -> data + offset , buffer , nbytes);

	else 

		memcpy(buffer ,dev -> data + offset , nbytes);

	return ;

}

void my_request ( struct request_queue *q )

{
	struct request *req;

	struct bio_vec *bvec ;

	struct bio *bio ;

	struct blk_dev *dev = NULL ;

	char *buffer = NULL ;

	printk ("+request function has been called \n");

	req = blk_fetch_request(q);

	while (req != NULL) {

		if (req == NULL /*|| (req->cmd_type != REQ_TYPE_FS)*/) {

			__blk_end_request_all(req, -EIO);

			continue;
		}

		dev = req -> rq_disk -> private_data ;

		bio = req -> bio ;

#ifdef BIO

		printk("bi_sector %u\n" , bio -> bi_iter . bi_sector);

		printk("bi_next %x\n" , bio -> bi_next);

		printk("bi_flags %lu\n" , bio -> bi_flags);

		printk("bi_vcnt %lu\n" , bio -> bi_vcnt);

		printk("bi_idx %lu\n" , bio -> bi_iter .  bi_idx);

#endif

		bvec = req -> bio -> bi_io_vec ;

#ifdef BIO_VEC 

		printk("bvec len %lu\n" , bvec -> bv_len);

		printk("bvec offset %lu\n" , bvec -> bv_offset);

#endif

		/* magic magic */

		buffer = kmap ( (struct page*) bvec -> bv_page )  ;

		blk_operations ( dev , 0 , 1 , buffer , rq_data_dir(req) ) ;

		kunmap( (struct page*) bvec -> bv_page) ;

		if ( ! __blk_end_request_cur(req, 0) ) {

			req = blk_fetch_request(q);
		}

		return  ;
	}

}

int device_open (struct block_device *bd, fmode_t mode)
{
	printk("+device open successful \n");

	return 0 ;
}

void device_close (struct gendisk *gd, fmode_t mode )
{
	printk("+device close successful \n");

	return  ;

}

int device_ioctl (struct block_device *bd , fmode_t mode , unsigned command, unsigned long addr)
{
	char *address = NULL ;

	address = ( char *) addr ;

	if ( !( (unsigned long ) GET_NAME  == command ) ) return -ENOTTY ;

	copy_to_user ( /*dest*/ address , /*src*/ bd -> bd_disk -> disk_name , /*size to transfer */ 32 ) ; 

	printk("+Ioctl called successfullt\n");

	return 0 ;

}

struct block_device_operations device_ops ={

	.owner = THIS_MODULE ,

	.open = device_open ,

	.release = device_close ,

	//.ioctl = device_ioctl,

};

int device_init_module ( void )
{

	/* step 1 : get a major number */

	major_number = register_blkdev ( major_number , DEVICE_NAME ) ;

	if ( major_number <= 0 ) {

		printk("-failed to get major number\n");

		return 1 ;
	}

	/* allocating memory fo virtual disk */

	my_inst = kmalloc ( sizeof ( struct blk_dev ) , GFP_KERNEL ) ;

	if ( my_inst == NULL ) {

		printk ("-memory allocation failed\n");

		goto major ;

	}

	/*fill out the entire space with zeros */

	memset ( my_inst , 0 , sizeof (struct blk_dev) ) ;

	/* fill out essential details about virtual disk */

	my_inst -> size = 1024*512 ; /* disk size */

	my_inst -> data = NULL ;

	my_inst -> data = kmalloc ( 1024*512 , GFP_KERNEL ) ; /* allocate memory for data */

	if ( my_inst -> data == NULL ) {

		printk ("-memory allocation failed\n");

		goto data ;

	}

	spin_lock_init ( &my_inst -> lock ) ;

	/* allocate a request queue descriptor and initializes most of the members with their default values */

	/* lock is to lock gendisk -> request_queue -> queue_lock and gendisk -> request_queue -> request_fn */ 

	my_inst -> queue = blk_init_queue ( my_request , &my_inst -> lock ) ;

	if ( my_inst -> queue == NULL ) {

		printk ("-queue initialization failed\n");

		goto memalloc ;

	}

	my_inst -> gdisk = alloc_disk ( 16 ) ;

	if ( my_inst -> gdisk == NULL ) {

		printk ("-alloc disk has failed\n");

		goto queue ;

	}

	my_inst -> gdisk -> major = major_number ;

	my_inst -> gdisk -> first_minor = 0 ;

	my_inst -> gdisk -> fops = &device_ops;

	my_inst -> gdisk -> queue = my_inst -> queue ;

	my_inst -> gdisk -> private_data = my_inst ;

	snprintf (my_inst -> gdisk -> disk_name, 32, DEVICE_NAME );

	set_capacity ( my_inst -> gdisk  , 1024) ;

	/* kobj_map to link major num & minor numbers & device dricer 

	   registers kobject in gdisk into /sys/block/uma_blk

	   registers queue into /sys/block/uma_blk/queue */

	/* add it to the list of active disks */

	add_disk ( my_inst -> gdisk ); 

	return 0 ;

	/* here comes the all important validations */

queue:
	blk_cleanup_queue( my_inst -> queue  );

data:
	kfree ( my_inst -> data ) ;

memalloc:

	kfree ( my_inst ) ;
major:
	unregister_blkdev ( major_number , DEVICE_NAME ) ;

	flag = 0 ;	

	return 1 ;

}
void device_cleanup_module ( void ) 
{	
	if ( flag ) {

		del_gendisk( my_inst -> gdisk ) ;

		put_disk(my_inst -> gdisk);

		kfree ( my_inst -> data ) ;

		kfree ( my_inst ) ;

		blk_cleanup_queue( my_inst -> queue  );

		unregister_blkdev ( major_number , DEVICE_NAME ) ;

	}

	printk("+unloaded the module\n");

}

MODULE_AUTHOR("saraboju umaraju charY");

MODULE_DESCRIPTION ("disk emulation");

module_exit ( device_cleanup_module ) ;

module_init ( device_init_module ) ;

MODULE_LICENSE("GPL v2");

/******************* END OF DEVICE DRIVER ****************/

