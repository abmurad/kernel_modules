


obj-m:=char_device.o

KDIR:=/lib/modules/$(shell uname -r)/build

KBUILD_EXTRA_SYMBOLS:=/lib/modules/4.6.3/kernel/drivers/syms/Module.symvers

PWD:=$(shell pwd)

all:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -w -o app_char _val.c app_char.c

insert:
	insmod char_device.ko 
c:	
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rm -f Module.symvers app_kmod
	-rmmod char_device
	rm app_char

