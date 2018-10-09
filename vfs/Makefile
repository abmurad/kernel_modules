#obj-m:=path.o

obj-m:=sub.o

#obj-m:=inode.o

#obj-m:=all.o

#obj-m:= my_module.o

#obj-m+=path3.o

#obj-m:=mem_map.o

#obj-m:=patherrupt.o prpath_key.o

#obj-m:=task_work.o


KDIR:=/lib/modules/$(shell uname -r)/build

KBUILD_EXTRA_SYMBOLS:=/lib/modules/$(shell uname -r)/kernel/drivers/syms/Module.symvers

#CFLAGS += -w

PWD:=$(shell pwd)

all:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules
	sudo dmesg -C

i:
	#insmod path3.ko
	insmod path.ko devname=device
#	insmod prpath_key.ko
#	insmod patherrupt.ko
#	insmod task_work.ko
c:	
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rm -f Module.symvers app_kmod
	
	rmmod path
	
#	rmmod path
	
#	rmmod patherrupt
	
#	rmmod prpath_key
	
	#rmmod task_work
