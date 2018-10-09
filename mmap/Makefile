obj-m:=mmap.o

KDIR:=/lib/modules/$(shell uname -r)/build

KBUILD_EXTRA_SYMBOLS:=/lib/modules/4.6.3/kernel/drivers/syms/Module.symvers

PWD:=$(shell pwd)

all:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules
i:
	#insmod basic_device_backup.ko name=device
	#insmod ls_own.ko devname=mychar2
#	rmmod read_cr0
#	rmmod basic_device_backup
#	rmmod ls_own
#	rmmod read_write
#	rm ./killer_whale
t:
	dmesg -C ; make c ;dmesg -C ; make c ; make  ; make i ; dmesg ; 
cpy:	
	cp *.ko /lib/modules/4.6.3/my_own2/
	depmod -a

