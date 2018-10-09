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

void hello_function(void);

void hello_function( void ) {

	printk("Iam a useless function \n");

	return ;

}

EXPORT_SYMBOL ( hello_function ) ;

int init_module(void)

{



	char *arr[] = { 
		" Virtual 8086 Mode Extensions" , 
		" Protected-mode Virtual Interrupts" , 
		" Time Stamp Disable" , 
		" Debugging Extensions" , 
		" Page Size Extension" , 
		" Physical Address Extension" , 
		" Machine Check Exception" , 
		" Page Global Enabled" ,
		" Performance-Monitoring Counter enable" , 
		" Operating system support for FXSAVE and FXRSTOR instructions" , 
		" Operating System Support for Unmasked SIMD Floating-Point Exceptions" ,
		" ",
		" ", 
		" Virtual Machine Extensions Enable" ,
		" Safer Mode Extensions Enable" , 
		" no bit",
		" Enables the instructions RDFSBASE, RDGSBASE, WRFSBASE, and WRGSBASE" , 
		" PCID Enable" , 
		" XSAVE and Processor Extended States Enable" ,
		" " ,
		" Supervisor Mode Execution Protection Enable" , 
		" Supervisor Mode Access Protection Enable" ,
		" protection key enabled" ,
		" " , 
		" " ,
		" " , 
		" " ,
		" " ,
		" " ,
		" " ,
		" " ,
		" " , } ;


	int index = 0 ;

	unsigned int cr4 = 0 ;

	asm volatile ( "mov %%cr4 , %0": "=r"(cr4) ) ;

	while ( index < 32  ) {

		if ( ( cr4 >> index  ) & 1 )  

			printk ("%s is enabled\n" ,arr[index] ) ;

		else 
			printk ("%d %s is disabled\n" , index , arr[index] );

		index++ ;

	}

	printk("init module\n");

	return 0;
}


void cleanup_module(void)
{

	char *arr[] = {
		" Virtual 8086 Mode Extensions" ,
		" Protected-mode Virtual Interrupts" ,
		" Time Stamp Disable" ,
		" Debugging Extensions" ,
		" Page Size Extension" ,
		" Physical Address Extension" ,
		" Machine Check Exception" ,
		" Page Global Enabled" ,
		" Performance-Monitoring Counter enable" ,
		" Operating system support for FXSAVE and FXRSTOR instructions" ,
		" Operating System Support for Unmasked SIMD Floating-Point Exceptions" ,
		" ",
		" ",
		" Virtual Machine Extensions Enable" ,
		" Safer Mode Extensions Enable" ,
		" no bit",
		" Enables the instructions RDFSBASE, RDGSBASE, WRFSBASE, and WRGSBASE" ,
		" PCID Enable" ,
		" XSAVE and Processor Extended States Enable" ,
		" " ,
		" Supervisor Mode Execution Protection Enable" ,
		" Supervisor Mode Access Protection Enable" ,
		" protection key enabled" ,
		" " ,
		" " ,
		" " ,
		" " ,
		" " ,
		" " ,
		" " ,
		" " ,
		" " , } ;

	int index = 0 ;


	unsigned int cr4 = 0 ;

	GPF_DISABLE ;

	unsigned char data = 'X' ;
	unsigned short port = 0x64 ;
	asm volatile("out %0,%1" : : "a" (data), "d" (port));


	asm volatile ( "mov %%cr4 , %0": "=r"(cr4) ) ;

	while ( index < 32  ) {

		if ( ( cr4 >> index  ) & 1 )

			printk ("%s is enabled\n" ,arr[index] ) ;

		else
			printk ("%d %s is disabled\n" , index , arr[index] );

		index++ ;

	}

	GPF_ENABLE ;

	printk(KERN_ALERT "*************************************************************\n");

}  

MODULE_LICENSE("GPL");
