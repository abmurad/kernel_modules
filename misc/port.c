#include	<linux/module.h>
#include	<linux/init.h>
#include	<linux/ioport.h>
/*
struct resource {
    resource_size_t start;
    resource_size_t end;
    const char *name;
    unsigned long flags;
    unsigned long desc;
    struct resource *parent, *sibling, *child;
};
*/

#define FROM 0x55

#define LEN 2

int flag = 1 ;

int init_module( void )
{
	struct resource *inst = NULL ;

	char *str = "XY";

	char addr[2] ;

	inst = request_region ( FROM , LEN , "uma_region" ) ;

	if ( !inst ) {
	
		flag = 0 ;

		printk("failed to allocate port region\n");

		return 1 ;

	}

	printk("allocation successfull %x\n" , inst );

	outsw ( 0x55 , (void*)str , 2 ) ;
	
	printk("%x %x\n" , addr[0] , addr[1] );

	insw ( 0x55 , &addr , 2 ) ;

	printk("%x %x\n" , addr[0] , addr[1] );

	return 0 ;
}

void cleanup_module ( void )
{
	if ( flag ) {
		
		release_region ( FROM , LEN ) ;
	}
	
	return ;
}

MODULE_LICENSE ( "GPL" );
