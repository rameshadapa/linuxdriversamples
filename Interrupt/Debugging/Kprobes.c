#if 0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

struct kprobe  kp = 
{

	.symbol_name = "do_fork"

};

static int handler_pre(struct kprobe *kp, struct pt_regs *regs)
{

	printk(" pre_handler : kp->addr = 0x%p, ip ; %lX, flags = %lX\n", kp->addr, regs->ip, regs->flags);
	return 0;

}

static void handler_post(struct kprobe *kp, struct pt_regs *regs, unsigned long flags)
{
	printk(" post_handler : kp->addr = 0x%p, ip ; %lX, flags = %lX\n", kp->addr, regs->ip, regs->flags);
}

static int handler_fault(struct kprobe *kp, struct pt_regs *regs, int trapnr)
{
	printk("fault_handler: p->addr = 0x%p, trap %d \n", kp->addr, trapnr);
	return 0; 

}


static int __init Init(void)
{


	int ret;

	kp.pre_handler = handler_pre;
	kp.post_handler = handler_post;
	kp.fault_handler = handler_fault;

	ret = register_kprobe(&kp);

	if(ret < 0)
	{

		printk(" Failed to register the kprobe \n");
		return -1;

	}


	printk(" Kprobe planted at the address : %p \n", kp.addr);
	return 0;

}

static void __exit Exit(void)
{

	unregister_kprobe(&kp);
	printk(" Kprobes are unregistered \n");

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");

#endif


#if 0
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>

struct kprobe kp;

static int handler_pre(struct kprobe *kp, struct pt_regs *regs)
{

	printk(" pre_handler : kp->addr = 0x%p, ip ; %lX, flags = %lX\n", kp->addr, regs->ip, regs->flags);
	return 0;

}

static void handler_post(struct kprobe *kp, struct pt_regs *regs, unsigned long flags)
{
	printk(" post_handler : kp->addr = 0x%p, ip ; %lX, flags = %lX\n", kp->addr, regs->ip, regs->flags);
}

static int handler_fault(struct kprobe *kp, struct pt_regs *regs, int trapnr)
{
	printk("fault_handler: p->addr = 0x%p, trap %d \n", kp->addr, trapnr);
	return 0; 

}


static int __init Init(void)
{

	int ret;

	kp.addr = kallsyms_lookup_name("do_fork");

	kp.pre_handler = handler_pre;
	kp.post_handler = handler_post;
	kp.fault_handler = handler_fault;

	ret = register_kprobe(&kp);
	if(ret < 0)
	{

		printk(" Kprobe is failed to register \n");
		return -1; 

	}
	printk(" kprobe is planted at the address: %p \n", kp.addr);
	return 0;


}

static void __exit Exit(void)
{


	printk(" kprobe is removed at the address %p \n", kp.addr);
	unregister_kprobe(&kp);
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");

#endif


#if 1

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/kprobes.h>

static int handler_pre(struct kprobe *kp, struct pt_regs *regs)
{

	printk(" %s function gets called \n", __func__);
//	*(unsigned char *) 0x0 = 10; // This is sucking. Closing down the entire system
	return 0;

}

static void handler_post(struct kprobe *kp, struct pt_regs *regs, unsigned long flags)
{

	printk(" %s function gets called \n", __func__);

}

static int handler_fault(struct kprobe *kp, struct pt_regs *regs, int trapnr)
{

	printk(" %s function gets called with the trap : %d \n", __func__, trapnr);
	return 0;

}

struct kprobe kp = 
{

	.pre_handler = handler_pre,
	.post_handler = handler_post,
	.fault_handler = handler_fault

};
static int __init Init(void)
{

	kp.addr = kallsyms_lookup_name("a_jprobe");
	if(register_kprobe(&kp) < 0)
	{
		printk(" The kprobe is failed \n");
		return -1;
	}

	return 0;

}

static void __exit Exit(void)
{

	unregister_kprobe(&kp);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");

#endif
