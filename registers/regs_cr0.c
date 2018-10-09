#ifndef __LINUX_FDTABLE_H
#define __LINUX_FDTABLE_H
#endif

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

#define GPF_DISABLE write_cr0(read_cr0() & (~ 0x00010000))
#define GPF_ENABLE write_cr0(read_cr0() | 0x00010000)


int init_module(void)

{


	printk("init module\n");

	char *arr[] = { 
		" 0 protect mode enabled" , 
		" 1 monitor coprocessor" , 
		" 2 emulation" , 
		" 3 task switched" , 
		" 4 Extension type" , 
		" 5 numeric error" , 
		" 6 none" , 
		" 7" ,
		" 8" ,
		" 9" ,
		" 10" ,
		" 11" ,
		" 12" ,
		" 13" ,
		" 14" ,
		" 15" ,
		" 16 write protect" , 
		" 17 none" ,
		" 18 allign mask",
		" 19", 
		" 20" ,
		" 21" ,
		" 22" ,
		" 23" ,
		" 24" ,
		" 25" ,
		" 26" ,
		" 27" ,
		" 28" ,
		" 29 not wtite through" ,
		" 30 cache disable" , 
		" 31 paging", } ;

		int index = 0 ;

		unsigned int cr0 = 0 ;

		asm volatile ( "mov %%cr0 , %0": "=r"(cr0) ) ;
		
		while ( index < 32  ) {

			if ( ( cr0 >> index  ) & 1 )  

				printk ("%s is enabled\n" ,arr[index] ) ;

			else 
				printk ("%d %s is disabled\n" , index , arr[index] );

				index++ ;

		}

		return 0;
	}


	void cleanup_module(void)
	{

		printk(KERN_ALERT "*************************************************************\n");
	
		GPF_DISABLE ;

		   char *arr[] = {
                " 0 protect mode " ,
                " 1 monitor coprocessor" ,
                " 2 emulation" ,
                " 3 task switched" ,
                " 4 Extension type" ,
                " 5 numeric error" ,
                " 6 none" ,
                " 7" ,
                " 8" ,
                " 9" ,
                " 10" ,
                " 11" ,
                " 12" ,
                " 13" ,
                " 14" ,
                " 15" ,
                " 16 write protect" ,
                " 17 none" ,
                " 18 allign mask",
                " 19",
                " 20" ,
                " 21" ,
                " 22" ,
                " 23" ,
                " 24" ,
                " 25" ,
                " 26" ,
                " 27" ,
                " 28" ,
                " 29 not wtite through" ,
                " 30 cache disable" ,
                " 31 paging", } ;

                int index = 0 ;

                unsigned int cr0 = 0 ;

                asm volatile ( "mov %%cr0 , %0": "=r"(cr0) ) ;

                while ( index < 32  ) {

                        if ( ( cr0 >> index  ) & 1 )

                                printk ("%s is enabled\n" ,arr[index] ) ;

                        else
                                printk ("%d %s is disabled\n" , index , arr[index] );

                                index++ ;

                }

	
		GPF_ENABLE ;
	
		printk(KERN_ALERT "*************************************************************\n");

	}  

	MODULE_LICENSE("GPL");
