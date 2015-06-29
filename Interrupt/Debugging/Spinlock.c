#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>

DEFINE_SPINLOCK(spinlock);

static int __init Init(void)
{

	spin_lock(&spinlock);
	spin_lock(&spinlock);
	//BUG: Spinlock recursion on cpu #0. kernel_Hacking-->spin_lock&rw_lock basic check
	return 0;

}

static void __exit Exit(void)
{
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
