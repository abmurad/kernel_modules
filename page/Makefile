


obj-m:=page.o

KDIR:=/lib/modules/$(shell uname -r)/build

KBUILD_EXTRA_SYMBOLS:=/lib/modules/4.6.3/kernel/drivers/syms/Module.symvers

#EXTRA_CFLAGS += -std=c90

PWD:=$(shell pwd)

none:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules
	dmesg -C
#	gcc app_blk.c _val.c -o app_blk

i:
	insmod page.ko

c:	
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rm -f Module.symvers app_kmod
	rmmod page

