# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
        obj-m := maK_it.o

# Otherwise we were called directly from the command
# line; invoke the kernel build system.
        KERNELDIR ?= /lib/modules/$(shell uname -r)/build
         PWD := $(shell pwd)
default:
	make -C $(KERNELDIR) M=$(PWD) modules
