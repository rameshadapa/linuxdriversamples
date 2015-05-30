ifeq ($(KERNELRELEASE),)
KERNEL_SOURCE := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) modules
	gcc -o user_prog user_prog.c
clean:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) clean
	rm user_prog
else
	obj-m := char_dev_sample.o
endif
