#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init Init(void)
{

	char *p = NULL;
/*
BUG: unable to handle kernel NULL pointer dereference at   (null)
[  826.756844] EIP: 0060:[<f84d5005>] EFLAGS: 00210246 CPU: 0
[  826.756846] EIP is at Init+0x5/0x1000 [Symoops1]
[  826.756848] EAX: 00000000 EBX: 00000000 ECX: 00200002 EDX: 00000670
[  826.756849] ESI: 0000129f EDI: 00000001 EBP: f20b3eec ESP: f20b3eec
[  826.756850]  DS: 007b ES: 007b FS: 00d8 GS: 00e0 SS: 0068
[  826.756852] Process insmod (pid: 3489, ti=f20b2000 task=f3330cb0 task.ti=f20b2000)
root@charan-VirtualBox:/home/charan/Interrupt/Debugging# gdb Symoops1.ko 
(gdb) list *(Init+0x5)
0x29 is in Init (/home/charan/Interrupt/Debugging/Symoops1.c:12).
7	
8		char *p = NULL;
9	
10	
11	
12		*p = 10;
13		return 0;
14	
15	}
16	
(gdb) q

*/




	*p = 10;
	return 0;

}

static void __exit Exit(void)
{
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
