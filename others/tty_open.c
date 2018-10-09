#include <stdio.h>

int main ( void ) 
{
	FILE *fp = fopen ( "/dev/pts/2" , "w" ) ;

	perror("file");

		printf("%p\n" , fp);
		printf("%p\n" , fp -> _IO_read_ptr);

	fprintf(fp , "%s" , "uma is good boy");
		printf("%p\n" , fp -> _IO_read_ptr);

	return 0 ;

}
