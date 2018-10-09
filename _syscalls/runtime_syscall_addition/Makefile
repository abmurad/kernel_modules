obj-m := rsysadd.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

	cp Module.symvers ./samples/

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
