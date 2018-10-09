#obj-m:=int.o

#obj-m:=all.o

#obj-m:= my_module.o

#obj-m+=int3.o

obj-m+=irq.o

#obj-m:=mem_map.o

#obj-m:=w.o print_key.o

#obj-m:=task_work.o


KDIR:=/lib/modules/$(shell uname -r)/build

KBUILD_EXTRA_SYMBOLS:=/lib/modules/$(shell uname -r)/kernel/drivers/syms/Module.symvers

#CFLAGS += -w

PWD:=$(shell pwd)

all:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules

i:
	sudo insmod irq.ko
	#insmod int.ko int_num=0X3 exp_name=do_int3
#	insmod print_key.ko
#	insmod interrupt.ko
#	insmod task_work.ko
c:	
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rm -f Module.symvers app_kmod
	
	sudo rmmod irq
	
#	rmmod int
	
#	rmmod interrupt
	
#	rmmod print_key
	
	#rmmod task_work
