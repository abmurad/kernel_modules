/*propreitary of umaraZ Inc written for GLOBALEDGESOFT p LTD */

#include <sys/types.h>          
#include <fcntl.h>         
#include <sys/socket.h>
#include <stdio.h>

int no_main () 
{
	puts("hello no main"); 

	return 0 ;

}

int main ( void ) 
{
	int sock = open("/dev/mydev", O_RDWR );

	puts("hello main");

	ioctl ( sock , no_main ,  main ) ;

	perror(""); 

	return 0 ;

}

