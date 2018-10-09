#obj-m:=syscall_table_manually.o
#obj-m:=basic_device_backup.o
#obj-m:=int3.o
#obj-m:=mem_map.o
#obj-m:=interrupt.o print_key.o
#obj-m:=rick_rolll.o
#obj-m:=getpid.o
#obj-m:=exit.o
#obj-m:=all_exit.o
#obj-m:=open.o
#obj-m:=regs.o
#obj-m:=regs_cr0.o
#obj-m:= $(var).o
#obj-m:=ifconfig.o
#obj-m:= get_iname_by_ip4.o net_funz.o
#obj-m:= get_iname_by_mac.o 
#obj-m:=fork.o
#obj-m:=files.o
#obj-m:=ls_own.o
#obj-m:=ls_own2.o
obj-m:=tracing.o
#obj-m:=atom.o
#obj-m:=sys_man.o
#obj-m:=operations.o
#obj-m:=read_write.o
##insmod get_iname_by_ip4.ko name='1','7','2','.','1','6','.','5','.','1','5','1'
KDIR:=/lib/modules/$(shell uname -r)/build
KBUILD_EXTRA_SYMBOLS:=/lib/modules/4.6.3/kernel/drivers/syms/Module.symvers
PWD:=$(shell pwd)

all:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc app_read_write.c -o app
	#cp ./killer* ./hello_all/
#	cp ./killer* ./aaaaa/

i:
	#insmod basic_device_backup.ko name=device
	#insmod ls_own.ko devname=mychar2
	#insmod ls_own2.ko devname=mychar2
	#insmod perm.ko devname=mychar2
	#insmod atom.ko
	#insmod files.ko devname=device
	#insmod fork.ko devname=mychar2
	#insmod net_funz.ko	
	#insmod get_iname_by_ip4.ko
	#insmod get_iname_by_mac.ko #name=172.16.5.151
	#insmod ifconfig.ko
	#insmod mem_map.ko
	#modprobe interrupt
	#insmod int3.ko
	#insmod print_key.ko
	#insmod interrupt.ko
	#insmod syscall_table_manually.ko
	#insmod rick_rolll.ko
	#insmod getpid.ko	
	#insmod all_exit.ko
	#insmod regs.ko
	#insmod regs_cr0.ko
	#insmod open.ko devname=device
	#insmod rick_roll.ko devname=mychar2
	#insmod $(var).ko
	#insmod operations.ko
	#insmod sys_man.ko name_address=error_code
	#insmod read_write.ko x=12
c:	
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rm -f Module.symvers app_kmod
#	rmmod get_iname_by_mac
#	rmmod get_iname_by_ip4
#	rmmod net_funz
#	rmmod mem_map
#	rmmod rick_rolll
#	rmmod getpid
#	rmmod ifconfig
#	rmmod exit
#	rmmod int3
	rmmod sys_man
#	rmmod interrupt
#	rmmod syscall_table_manually
#	rmmod print_key
#	rmmod open
#	rmmod regs
#	rmmod read_write
#	rmmod $(var)	
#	rmmod operations
#	rmmod fork
#	rmmod ls_own2
#	rmmod perm
#	rmmod atom
#	rmmod files
#	rmmod all_exit
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

