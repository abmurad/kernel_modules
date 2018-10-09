#include	<stdio.h>
#include	<string.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	<sys/mman.h>

int main ( void ) 
{
	int fd = 0 ;

	if (  0 > ( fd = open ( "/dev/uma_char" , O_RDWR )  ) ) {

		perror("opne");

		return 1 ;
	
	}

	char rb[100] ={};

	int ch = 0 ;

	void *addr = NULL ;

	while (1) {

	ch = _val("your choice\n1)read\n2)write\n3)mmap\n");

	switch ( ch ) {

		case 2 : 

			//printf("enter data\n");
			
			write ( fd , "hello_world_of_programmers", 30 ) ;

			puts("data has been written successfully");

			break ;

		case 1 :

			read ( fd , rb, 30 ) ;

			printf("data is %s\n",rb);

			break ;

		case 3 : 
				addr = mmap ( NULL , 8191 , PROT_READ | PROT_WRITE , MAP_SHARED , fd , 0 ) ;

				perror("mmap");

				printf("address returned by mmap n is %x\n" , addr);

				printf("data is %s\n",addr);

				strcpy ( addr , "dabba");
				
				break;

			

	}

	}
	close ( fd ) ;

	return 0 ;

}
