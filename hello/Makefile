ifneq ($(KERNELRELEASE), )
obj-m := hello.o
else
KDIR := /usr/src/linux-headers-$(shell uname -r)

all:
	$(MAKE) -C $(KDIR) M=$$PWD
endif
