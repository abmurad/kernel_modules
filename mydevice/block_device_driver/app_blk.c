#include	<stdio.h>

#include	<stdio_ext.h>

#include	<string.h>

#include	<fcntl.h>

#include	<stdlib.h>

#include	"ioctl_commands.h"

#include	<sys/mman.h>

int main ( void ) 
{
	int fd = 0 ;

	if ( ( fd = open ( "/dev/disk_local" , O_RDWR )  ) < 0  ) {

		perror("opne");
		
		return 1 ;
	
	}
	
	char wb[30] = {} ;

	char rb[30] = {} ;

	void *addr = NULL ;

	char buffer[32] = {} ;

	int ch = _val("your choice \n1)read \n2)write \n3)ioctl");

	switch ( ch ) {

		case 2 : 

			printf("enter data to write into disk\n");
			
			__fpurge(stdin) ;

			fgets ( wb , 29 , stdin ) ;

			write ( fd , wb, sizeof( wb ) ) ;

			break ;

		case 1 :

			read ( fd , rb, sizeof( rb ) ) ;

			__fpurge(stdin) ;

			printf("data is : %s\n",rb);

			break ;

		case 3 :

			ioctl(fd , GET_NAME , (unsigned long) buffer);

			perror("ioctl");

			printf("disk name is: %s\n" , buffer);
			
			break ;

		default :
	
			printf("that isnt a valid choice\n");
		
			break;

	}
	
	close ( fd ) ;

	return 0 ;

}
