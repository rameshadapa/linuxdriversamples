all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
EXTRA_CFLAGS = -DDEBUG
#obj-m:=Symoops1.o
#obj-m:=SchedulingWhileAtomicBug.o
#obj-m:=DynamicPrintingOfVars.o
obj-m:= Kmemleak.o
