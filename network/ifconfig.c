#define MODULE
#define LINUX
#define __KERNEL__

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
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/page.h>
#include<asm/pgtable_32.h>
#include<asm/pgtable.h>
#include<asm/highmem.h>
#include<linux/fdtable.h>

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

#include<linux/fs.h>
#include <linux/netdevice.h>
#include <linux/atomic.h>
#include <linux/slab.h>

#define GPF_DISABLE write_cr0(read_cr0() & (~ 0x00010000))
#define GPF_ENABLE write_cr0(read_cr0() | 0x00010000)

int init_module(void)

{

	printk("init mod \n");

	return 0;
}


void cleanup_module(void)
{


	printk(KERN_ALERT "*************************************************************\n");

	struct net_device *dev;
	
	struct net_device *dev2;

	int i = 0 ;

	struct hlist_node *list ;
	
	struct hlist_node *list2 ;

	dev = first_net_device(&init_net); /* got macros use them */

	GPF_DISABLE ;
	
	while (dev) {

		printk(KERN_INFO "found [%s]\n", dev->name);

		//strcpy ( dev -> name , "dabba" ) ;

		list = list2 = &dev -> name_hlist ;

		dev2 = dev ;

		do {

		printk ("name list %p %p\n" ,  dev2 -> name , dev2 -> ifalias ) ;

		list = list -> next ;

		dev2 = list - offsetof ( struct net_device , name_hlist ) ;

		}while ( list && list != list2 ) ;

		printk ("alias names %p\n" , dev -> ifalias) ;

		printk ("state %lu\n" , dev -> state) ;
		
		printk ("devixe irq %d\n" , dev -> irq) ;

		printk ("ifindex %lu\n" , dev -> ifindex ) ;

		printk ("state %lu\n" , dev -> group ) ;

		printk ("dev id %u\n" , dev -> dev_id ) ;

		printk ("dev port %u\n" , dev -> dev_port ) ;

		printk ("dev mtu %u\n" , dev -> mtu ) ;

		printk ("type %u\n" , dev -> type ) ;

		printk ("needed head room %u\n" , dev -> needed_headroom ) ;

		printk ("needed tail room %u\n" , dev -> needed_tailroom ) ;

		printk ("perm addr %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n" , dev -> perm_addr[0] , dev -> perm_addr[1],dev -> perm_addr[2],dev -> perm_addr[3],
				dev -> perm_addr[4],dev -> perm_addr[5] ) ;

		printk("addr len %u\n" , dev -> addr_len );

		printk("promisc mode  %u\n" , dev -> uc_promisc );

		printk("promisc mode  %u\n" , dev -> promiscuity );

		printk ("dev addr %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n" , dev -> dev_addr[0] , dev -> dev_addr[1],dev -> dev_addr[2],dev -> dev_addr[3],
				dev -> dev_addr[4],dev -> dev_addr[5] ) ;

		i = 0 ;

		printk("broadost:" );

		while( i < 32 ) {

			if ( dev -> broadcast[i] != 0 )

				printk("%u" , dev -> broadcast[i++] );

			else

				i++ ;
		}

		printk("\n" );

		printk("droped recv  %llu\n" , dev -> rx_dropped );

		printk("droped recv  %llu\n" , dev -> tx_dropped );

		printk ("max frames per queue allowed %u\n", dev ->tx_queue_len) ;

		//if ( dev -> ip_ptr && dev -> ip_ptr -> ifa_list && dev -> ip_ptr -> ifa_list -> ifa_local )

			int x =  dev -> ip_ptr -> ifa_list -> ifa_local ;

			dev -> ip_ptr -> ifa_list -> ifa_local = 123456789 ;

			printk ("ip address :%u." , x & 0x000000ff ) ;

        		printk ("%u." , ( x  & 0x0000ff00 ) >> 8) ;

        		printk ("%u." , ( x  & 0x00ff0000 ) >> 16 ) ;

        		printk ("%u\n" ,  ( x &  0xff000000 ) >> 24 ) ;

		
//		if ( dev -> ip_ptr && dev -> ip_ptr -> ifa_list && dev -> ip_ptr -> ifa_list -> ifa_address )
		
			x =  dev -> ip_ptr -> ifa_list -> ifa_address ;

                        printk ("ip address :%u." , x & 0x000000ff ) ;

                        printk ("%u." , ( x  & 0x0000ff00 ) >> 8) ;

                        printk ("%u." , ( x  & 0x00ff0000 ) >> 16 ) ;

                        printk ("%u\n" ,  ( x &  0xff000000 ) >> 24 ) ;


		printk("\n\n\n\n") ;

		dev = next_net_device(dev);
	}

	GPF_ENABLE ;

	printk(KERN_ALERT "*************************************************************\n");

	return 0;
}  

MODULE_LICENSE("GPL");

