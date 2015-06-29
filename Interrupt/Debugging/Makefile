all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
EXTRA_CFLAGS = -DDEBUG
#obj-m:=Symoops1.o
#obj-m:=SchedulingWhileAtomicBug.o
#obj-m:=DynamicPrintingOfVars.o
obj-m:= Kmemleak.o
#obj-m:= Proc_fs.o
#obj-m := Seq_fs.o
#obj-m:= Debug_fs.o
#obj-m := Kprobes.o
#obj-m := Jprobes.o
#obj-m :=Kretprobes.o
#bj-m := Spinlock.o
