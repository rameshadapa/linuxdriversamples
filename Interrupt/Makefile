all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
#obj-m := Driver1.o
#obj-m := kprobe.o
#obj-m := Tasklet.o
#obj-m := Workqueue.o
obj-m := Timers.o
#obj-m :=Synchronization.o
#obj-m := rbtree.o
#obj-m := mm.o
 
