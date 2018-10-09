#var=pctest

var=path

#var=port

#var=subdirs

#var=mod_syscall

#var=pgtab

#var=seqtest

#var=page_addr

#var=running

#var=sysinfo

#var=ps

#var=top

#var=vm_area

#var=swap_pg

#var=cmpr

#var=cpu_test

#var=runqueue

#obj-m+= class_register.o device_create.o device_register.o

#obj-m:=test_device.o test_driver.o

#obj-m:=contest.o v_t.o

#var=dcache

#var=misc

#var=intercept

#var=sysfs

#var=zonetest

#var=v_t

#var=running

#var=netdev

#var=kbd

#var=biotest

#var=contest

#var=current

#var=platform

#var=va_pa

#var=regulator

#var=kern_path

obj-m:=$(var).o

KDIR:=/lib/modules/$(shell uname -r)/build

KBUILD_EXTRA_SYMBOLS:=/lib/modules/4.6.3/kernel/drivers/syms/Module.symvers

#EXTRA_CFLAGS += -v

PWD:=$(shell pwd)

none:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules

i:
	sudo dmesg -C
	sudo insmod $(var).ko

c:	
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	sudo rm -f Module.symvers app_kmod
	sudo rmmod $(var)

v:
	vim $(var).c
t:
	make c ; make ; make i ; make c ;dmesg
