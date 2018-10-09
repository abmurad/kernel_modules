#include	<linux/init.h>

#include	<linux/module.h>

#include	<linux/fs.h>

#include	<linux/platform_device.h>

void platform_release ( struct device *dev ) 
{
	return ;
}
struct platform_device pdev = {
	
		.name = "uma_dev" ,

		.id = -1 ,

		.dev = {

				.release = platform_release ,
		
		}

};
static int __init platform_init( void ) 
{
	int ret = 0 ;
		
	ret = platform_device_register( &pdev ) ;

	return ret ;

}

static void __exit platform_exit ( void ) 
{
	platform_device_unregister ( &pdev ) ;

	return ;

}

module_init(platform_init);

module_exit(platform_exit);

MODULE_LICENSE ("GPL v2") ;
