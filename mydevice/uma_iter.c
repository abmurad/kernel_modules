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

#include <linux/spinlock.h>

#include <linux/wait.h>

#include <linux/mm.h>

#include <asm/highmem.h>

#include <linux/kallsyms.h>

#include <linux/jiffies.h>

#include <linux/moduleparam.h>

#define DEVICE_NAME "uma_iter"

MODULE_LICENSE("GPL");

/*int device_mmap ( struct file *filp , struct vm_area_struct *vma ) 
  {
  printk ("mmap calle successful\n");

  if ( remap_pfn_range ( vma , vma -> vm_start , ( ( func( &virtual_device ) ) << vma -> vm_pgoff)  , 8191 , vma -> vm_page_prot ) ) {


  printk("remap_pfn_range has failed\n");

  return 1 ;

  }

  return 0 ;	

  }
 */
static struct blk_major_name {

        struct blk_major_name *next;

        int major;

        char name[16];

} **major_names_local;


static struct char_device_struct {

        struct char_device_struct *next;

        unsigned int major;

        unsigned int baseminor;

        int minorct;

        char name[64];

        struct cdev *cdev;              /* will die */

}**chardevs;

int init_module ( void )
{

	struct my_virtual_device *dev = NULL ;

	chardevs = kallsyms_lookup_name("chrdevs");

	//      printk("chardevs is %x" , chardevs );

	int index = 0 ;

	struct char_device_struct *charinst ;

	printk ("%10s %10s %10s\n" , "major_number" , "minor_number" , "name");

	for ( index = 254 ; index > 0 ; index -- ) {

		charinst = chardevs[index] ;

		if ( charinst ) {

			printk ("%10u %10u %10s\t" , charinst -> major , charinst -> baseminor , charinst -> name);

			if  ( charinst -> cdev != NULL  ) {

				printk ( "kobject name is %s\t" ,charinst -> cdev -> kobj . name  ) ;

				if (  charinst -> cdev -> kobj . sd ) {

					printk ( "sysfs entry is %x \n" ,charinst -> cdev -> kobj . sd -> name ) ;

				} else printk("no sysfs entry %x\n" , charinst -> cdev -> kobj . sd) ;
			}

			else printk("no name\n");

		}

	}


	return 0 ;

}
void cleanup_module ( void ) 
{
	
	major_names_local = kallsyms_lookup_name ("major_names");	

	int index = 0 ;

        struct blk_major_name *blkinst ;

        printk ("%10s %10s\n" , "major_number" , "name");

        for ( index = 254 ; index > 0 ; index -- ) {

 		blkinst = major_names_local[index] ;

		if ( blkinst ) {

			 printk ("%10u %10s\n" , blkinst -> major , blkinst -> name);

		}//else printk("\n");

	}

	printk("unloades module\n");

}

//module_init ( clean_u ) ;
//module_exit ( init_u ) ;
