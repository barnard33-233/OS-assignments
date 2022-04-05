CONFIG_MODULE_SIG = n #to solve 'signature and/or required key missing'
obj-m += kptree.o

PWD := $(shell pwd)
KDIR := /lib/modules/$(shell uname -r)/build
EXTRA_CFLAGS= -O0

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

test:
	dmesg -c
	insmod kptree.ko
	rmmod kptree
	dmesg > dmesg.file
