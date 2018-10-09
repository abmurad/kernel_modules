
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int init_module(void *module_image, unsigned long len,
		const char *param_values);

int main(int c , char *v[]) 
{

	struct stat sb;

	int rc = 0;


	if  ( c < 2 ) {

		printf("usage: < %s > < module_names ... > \n" , v[0]);

		return 1 ;

	}

	rc = 1 ;

	while ( rc < c ) {

		if ( delete_module ( v[rc++] , O_NONBLOCK ) ) 

		perror("removing module");

	}
	return EXIT_SUCCESS;
}
