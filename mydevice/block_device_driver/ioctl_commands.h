#ifndef __IO_HEAD__

#define __IO_HEAD__

#include	<sys/ioctl.h>

#define IOCTL_MAGIC_NUMBER 'Z' 

#define GET_NAME _IOR(IOCTL_MAGIC_NUMBER, 0, unsigned long )

#endif
