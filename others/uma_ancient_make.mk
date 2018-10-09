TARGET  := basic_device_backup
WARN    := -W -Wall -Wstrict-prototypes -Wmissing-prototypes
INCLUDE := -I /lib/modules/`uname -r`/build/include/
#INCLUDE := -I /usr/src/linux-`uname -r`/include/
CFLAGS  := -O2 -DMODULE -D__KERNEL__ ${WARN} ${INCLUDE}
CC      := gcc-4.8
	
${TARGET}.o: ${TARGET}.c

.PHONY: clean

clean:
	rm -rf ${TARGET}.o
