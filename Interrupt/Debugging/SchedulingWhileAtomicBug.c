#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/preempt.h>
#include <linux/delay.h>
#include <asm/system.h>

static void Func(void);

static void Func(void)
{

	msleep(1000);



}
static int __init Init(void)
{

	printk(" %s \n", __func__);
	preempt_disable();
	barrier();
	smp_mb();

//	Func();
	msleep(1000);

	barrier();
	smp_mb();

	preempt_enable();
	return 0;

}

static void __exit Exit(void)
{

	printk(" %s \n", __func__);
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");

/*

[ 2846.182919] BUG: scheduling while atomic: insmod/4701/0x00000002
[ 2846.183026] Call Trace:
[ 2846.183035]  [<c15a1400>] ? printk+0x1a/0x2f
[ 2846.183040]  [<c15a1194>] __schedule_bug+0x5e/0x64
[ 2846.183046]  [<c15a8ee2>] __schedule+0x932/0x960
[ 2846.183052]  [<c10373a8>] ? default_spin_lock_flags+0x8/0x10
[ 2846.183057]  [<c105c54d>] ? console_unlock+0x21d/0x290
[ 2846.183061]  [<c10373a8>] ? default_spin_lock_flags+0x8/0x10
[ 2846.183065]  [<c15ab058>] ? _raw_spin_lock_irqsave+0x38/0x50
[ 2846.183070]  [<c15a91e5>] schedule+0x35/0x50

[ 2846.183074]  [<c15a961a>] schedule_timeout+0x13a/0x2c0
[ 2846.183079]  [<c106a260>] ? usleep_range+0x40/0x40
[ 2846.183084]  [<c15a97ba>] schedule_timeout_uninterruptible+0x1a/0x20
[ 2846.183087]  [<c106bd9d>] msleep+0x1d/0x30
[ 2846.183092]  [<f863a02e>] Init+0x2e/0x1000 [SchedulingWhileAtomicBug]
[ 2846.183096]  [<c1003035>] do_one_initcall+0x35/0x170
[ 2846.183101]  [<f863a000>] ? 0xf8639fff
[ 2846.183107]  [<c1097620>] sys_init_module+0x2c0/0x1bc0
[ 2846.183115]  [<c15ab244>] syscall_call+0x7/0x7


t@charan-VirtualBox:/home/charan/Interrupt/Debugging# gdb SchedulingWhileAtomicBug.ko 
(gdb) list *(Init+0x33)
0x57 is in Init (/home/charan/Interrupt/Debugging/SchedulingWhileAtomicBug.c:30).
25	
26	//	Func();
27		msleep(1000);
28	
29		barrier();
30		smp_mb();
31	
32		preempt_enable();
33		return 0;
34	
(gdb) list *(0xf863a033)
No source file for address 0xf863a033.

*/

/**** The list *<> is not giving the proper place. So, atlease we can get into the culprit  **CALLING** function, yes not the actual function ,  with the dump the caontains the Tag *** [SchedulingWhileAtomicBug] ***.
