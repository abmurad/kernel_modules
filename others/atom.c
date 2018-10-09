#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mmzone.h>
#include <linux/err.h>
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/compiler.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/fs.h>

#include <linux/atomic.h>
#include <asm/irq_vectors.h>
#include <asm/atomic.h>

int write_console(char*);

unsigned long lookup_own ( char *) ;

int init_module(void)

{

		printk("********************* initialization *************************\n");



#if 0
		atomic_t v ;

		int x = 0 ;

		atomic_set ( &v , 123 ) ;

		write_console("hello world module has been inserted");

		int c = 0 ;

		printk ( "do int3 is %x\n" , lookup_own ( "do_int3" ) ) ;

		while ( c < 31 ) {

				atomic_read(&v) & ( 1 << c ) ? printk("1"):printk("0");

				c++ ;

		}
		//	v = ATOMIC_INIT ( 12 ) ; //never worked for me

		printk("value of v is %d\n" , v );

		printk("value of v through atomic_read is %d\n" , atomic_read(&v) );

		atomic_add ( 12 , &v ) ; //return nothing

		//atomic_add_return will return 

		printk("value of v through atomic_add is %d\n" ,v );

		atomic_sub ( 12 , &v ) ;

		printk("value of v through atomic_sub is %d\n" ,v );

		atomic_inc ( &v ); 

		printk("value of v through atomic_inc is %d\n" ,v );

		atomic_dec ( &v ); 

		printk("value of v through atomic_dec is %d\n" ,v );

		c = atomic_sub_and_test ( 12 , &v ) ;

		printk("value of c through atomic_sub_and_test is %d\n" ,c );

		c = atomic_inc_and_test ( &v );

		printk("value of c through atomic_inc_and_test is %d\n" ,c );

		c = atomic_dec_and_test ( &v );

		printk("value of c through atomic_dec_test is %d\n" ,c );

#endif

		return 0;
}


void cleanup_module(void)
{

		printk(KERN_ALERT "*************************************************************\n\n\n");

		pg_data_t *inst = NULL ;

		printk ("size of struct zone %zu\n" , sizeof ( struct zone ) );

		printk (" num of irqs %d\n" , NR_IRQS );

		for_each_online_pgdat(inst) {

				printk ("%zu\n" , sizeof ( inst -> node_zones ) );

				printk ("name %s\n" ,  ( inst -> node_zones[0] . name ) );

				printk ("name %s\n" ,  ( inst -> node_zones[1] . name ) );

				printk ("name %s\n" ,  ( inst -> node_zones[2] . name ) );

				printk ("name %s\n" ,  ( inst -> node_zones[3] . name ) );

				//	printk ("NUMA %d\n" ,  ( inst -> node_zones[3] . node ) );

				printk ("nr_zones %zu\n" ,  ( inst -> nr_zones ) );

				printk ("node_mem_map %x mem_map %x sizeof struct page %zu sizeof mem_map %zu\n" ,  /*( inst -> node_mem_map )*/1 , mem_map , sizeof ( struct page ) , sizeof( mem_map ) );

				printk ("node_present_pages %zu\n" ,  ( inst -> node_present_pages ) );

				printk ("node_start_pfn %zu\n" ,  ( inst -> node_start_pfn ) );

		} 

		printk(KERN_ALERT "\n\n\n*************************************************************\n");

}  

MODULE_LICENSE("GPL");

