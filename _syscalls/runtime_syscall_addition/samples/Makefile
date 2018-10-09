obj-m := sys_give_root.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
CC := /usr/bin/gcc

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	$(CC) -o test test.c
	cp  Module.symvers ../

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm ./test
