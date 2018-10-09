
/*property of umasraZ Inc for globaledgesoft ltd */

#define LINUX

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
#include <linux/inetdevice.h>

#include <linux/netdevice.h>
#include <linux/atomic.h>
#include <linux/slab.h>

unsigned char name[] = { 0xdc, 0xfe, 0x07 ,0x00, 0xfe, 0xcc} ;

//module_param_array ( name , byte, &count , 0000 );

int init_module(void)

{
	if ( name == NULL ) {

		printk ( "provide ip addreess of interface \n" ) ;

		return 0 ;

	}

	return 0;
}

void cleanup_module(void)
{

	int mac_var = 0 ;
	
	struct net_device *dev;

	char *name2 = NULL ;

	printk(KERN_ALERT "*************************************************************\n");

	dev = first_net_device(&init_net);

	while (dev) {

		while ( mac_var < 6 ) {

			if (name[mac_var] == dev->perm_addr[mac_var])

				mac_var ++ ;
			
			else break ;

		}

		if ( mac_var == 6 ) { 

			name2 = dev -> name ;

			break ;
		}

			else mac_var = 0 ;

		dev = next_net_device(dev);
	}

	if ( name2 != NULL )

		printk ("you are searching for %s\n" , name2 );

		else 

		printk ("didnt find any interface\n");

	printk(KERN_ALERT "*************************************************************\n");

}  

MODULE_LICENSE("GPL");

