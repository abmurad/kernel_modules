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
#define FILE_NAME "./somefile"
static int __init hello_start(void)
{
    struct file* my_fd;

    my_fd = filp_open ("./tst", O_RDONLY, 0);
    if (IS_ERR (my_fd))
    {
    printk (KERN_ERR "Failed to open file. err: %d.\n", my_fd);
    }
    else
    {
    my_fd->f_op->write (my_fd, "some data", 10, &my_fd->f_pos);
    }

printk(KERN_INFO "Loading hello module...\n");
return 0;
}

static void __exit hello_end(void)
{
printk(KERN_INFO "hello_end.\n");
}

module_init(hello_start);
module_exit(hello_end);

#if 0
int init_module(void)

{

		printk("************initialiZation************\n");

//		mm_segment_t oldfs ;
		
//		oldfs = get_fs() ;

		loff_t pos = 0 ;

		char buf[12] = "" ;

//		set_fs(KERNEL_DS) ;

		printk ("%p %p %p\n" , KERNEL_DS , USER_DS, get_fs() ) ;

		struct file *f = filp_open ( FILE_NAME , O_RDWR , 0 ) ;

		if ( IS_ERR(f) || f == NULL ) {

			printk ("file opening fasiled %x\n",f) ;

			return 0 ;

		}

		printk("file opened for reading and writing\n");
		
		printk("file -> f_pos %lu \n" , f -> f_pos );

//		ssize_t vfs_write(struct file *file, const char __user *buf, size_t count, loff_t *pos)

		vfs_write ( f , "umalaz" , 7 , 	&pos ) ;
		
		printk(" af write file -> f_pos %lu \n" , f -> f_pos );

//		ssize_t vfs_read(struct file *file, char __user *buf, size_t count, loff_t *pos)

		vfs_read ( f , buf , 7 , &pos ) ;

		printk(" af read file -> f_pos %lu \n" , f -> f_pos );

		printk ("data is %s\n" , buf) ;	

//		set_fs ( oldfs) ;

		return 0;
}


void cleanup_module(void)
{
		
		printk(KERN_ALERT "*************************************************************\n");


		printk(KERN_ALERT "*************************************************************\n");

}  

MODULE_LICENSE("GPL");
#endif
