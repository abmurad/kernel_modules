#include <stdio.h>
#include <fcntl.h>
#include "ioctl_basic.h"  //ioctl header file

main ( ) {
 int fd;
        fd = open("/dev/temp", O_RDWR | O_CREAT);

        if (fd == -1)
        {
                printf("Error in opening file \n");
                exit(-1);
        }
       
 ioctl(fd,IOCTL_HELLO);  //ioctl call 
	perror("status");
         close(fd);
}
