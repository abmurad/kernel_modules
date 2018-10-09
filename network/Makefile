obj-m:=hook.o
#hooks-objs= hook.o net_funz.o

KDIR:=/lib/modules/$(shell uname -r)/

KBUILD_EXTRA_SYMBOLS:=/lib/modules/$(shell uname -r)/kernel/drivers/syms/Module.symvers

#CFLAGS += -w

PWD:=$(shell pwd)

all:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules

i:
	insmod hook.ko
c:	
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rm -f Module.symvers app_kmod
	
	rmmod hook
	
#	rmmod int
	
#	rmmod interrupt
	
#	rmmod print_key
	
	#rmmod task_work
