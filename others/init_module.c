
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int init_module(void *module_image, unsigned long len,
		const char *param_values);

int main(int c , char *v[]) {
	int res = 0;
	void *buf = 0;
	struct stat sb;
	int rc = 0;
	int i = 2 ;
	int len = 0 ;

	char *new = NULL ;

	if ( c < 2 ) {
		
		printf("usage: < %s > < module name > < parameter_name=value ... >\n" , v[0]);
	
		return 1 ;

	}
	
	new = malloc ( 1024 ) ;

	memset ( new , 0 , sizeof ( new ) ) ;

	i = 2 ;

	while ( i < c ) {
		
		strcat ( new , v[i++] ) ;
		
		strcat ( new , " " ) ;

	}

	int fd = open(v[1], O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	res = fstat(fd, &sb);
	if (res == -1) {
		perror("fstat");
		exit(EXIT_FAILURE);
	}

	buf = mmap(0, sb.st_size, PROT_READ|PROT_EXEC, MAP_PRIVATE, fd, 0);
	if (buf == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	
	if ( ! new ) 

		strcpy ( new , "" ) ;


	res = init_module(buf, sb.st_size, new );
	
	if (res == -1) {
		perror("**init_module");
		exit(EXIT_FAILURE);
	}

	munmap(buf, sb.st_size);
	close(fd);
	free(new);
	return EXIT_SUCCESS;
}
