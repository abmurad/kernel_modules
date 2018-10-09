
/*property of umasraZ Inc for globaledgesoft ltd */


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

char *int_ascii ( unsigned long int ) ;

char* _tok ( char *str , char* str2 ) ;

unsigned long int ascii_int(char*) ;

unsigned long int htonl_u ( unsigned long int ) ;

long long int _atoi( char *buf ) ;

unsigned char *name = "127.0.0.1" ;

unsigned long int ip_int = 0 ;

int count = 0 ;

//module_param_array ( name , byte, &count , 0000 );

int init_module(void)

{
	if ( name == NULL ) {

		printk ( "provide ip addreess of interface \n" ) ;

		return 0 ;

	}

	printk ("name count %u\n", count );

	return 0;
}

void cleanup_module(void)
{


	struct net_device *dev;
	
	char *name2 = NULL ;

	//unsigned long int x = ascii_int ( temp ) ;

	//printk ("cleanup module  %lu\n" , (x)) ;

	//printk ("name is %s\n", name);


	printk(KERN_ALERT "*************************************************************\n");

	dev = first_net_device(&init_net);

	while (dev) {
		
		
//		printk ("struct %s\n" , int_ascii(ntohl(dev-> ip_ptr -> ifa_list -> ifa_local)));
		
	//	printk ("command line %s\n" , name );
		
	//	printk ( "%d ascii_int \n" ,strlen (int_ascii(ntohl(dev-> ip_ptr -> ifa_list -> ifa_local)))) ;	

	//	printk ( "%d name\n" ,strlen (name)) ;

		if ( ! (strncmp ( int_ascii(ntohl(dev-> ip_ptr -> ifa_list -> ifa_local)) , name , strlen(name) ) ) ) {

			name2 = dev -> name ;

			}
		
		dev = next_net_device(dev);
	}
	
	if ( name2 != NULL )

	printk ("you are searching for %s\n" , name2 );
	
	printk(KERN_ALERT "*************************************************************\n");

}  

MODULE_LICENSE("GPL");

