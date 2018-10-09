#include <linux/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

#define IOCTL_OWN _IO(123, 12  )

int global = 0 ;

int main ()
{
	int pid = getpid ();

	printf("pid %d \n", pid);

	fopen("1.c" , "w");
	
	int fd = open ("/dev/device", O_RDWR );


	if (fd < 0)
	
		perror ("Unable to open the device\n");
	else 
		printf ("File opened Successfully %d\n", fd);
	
	ioctl ( fd , getpid() , main );

	perror("ioctl");

	close (fd);

	return 0;	
}
