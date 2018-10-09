#include<linux/ioctl.h>

#define IOCTL_MAGIC_NUMBER 99
#define IOCTL_LONGU _IOR(IOCTL_MAGIC_NUMBER, 0, unsigned long )
#define IOCTL_CHARP _IOW(IOCTL_MAGIC_NUMBER, 1, char *)
#define IOCTL_HELLO _IO(IOCTL_MAGIC_NUMBER, 2)

#define IOCTL_MAGIC_MAX 2

