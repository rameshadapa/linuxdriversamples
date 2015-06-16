all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
#obj-m := Driver1.o
#obj-m := kprobe.o
#obj-m := Tasklet.o
#obj-m := Workqueue.o
#obj-m := Timers.o
#obj-m :=Synchronization.o
#obj-m := rbtree.o
#obj-m := mm.o
#obj-m := fasync.o 
#obj-m := Test.o
#obj-m := Bus.o
#obj-m:=scatterlist.o
#obj-m := Misc.o
obj-m := complete_driver.o
