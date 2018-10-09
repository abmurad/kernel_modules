var=

obj-m:=$(var).o

KDIR:=/lib/modules/$(shell uname -r)/build

KBUILD_EXTRA_SYMBOLS:=/lib/modules/4.6.3/kernel/drivers/syms/Module.symvers

#EXTRA_CFLAGS += -std=c90

PWD:=$(shell pwd)

none:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules

i:
	dmesg -C
	insmod $(var).ko

c:	
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rm -f Module.symvers app_kmod
	rmmod $(var)

v:
	vim $(var).c
t:
	make c ; make ; make i ; make c ;dmesg
