
obj-m:=blk_device.o

KDIR:=/lib/modules/$(shell uname -r)/build

KBUILD_EXTRA_SYMBOLS:=/lib/modules/4.6.3/kernel/drivers/syms/Module.symvers

#EXTRA_CFLAGS += -std=c90

PWD:=$(shell pwd)

none:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc app_blk.c _val.c -o app_blk

insert:
	insert blk_device.ko

clean:	
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	dmesg -C
	@rm -f Module.symvers app_kmod
	-delete blk_device
	rm app_blk

