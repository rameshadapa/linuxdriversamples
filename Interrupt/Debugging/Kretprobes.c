#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/slab.h>
#include <linux/kallsyms.h>

void *jprobe_kmalloc(size_t size, gfp_t flags)
{

	printk(" In %s with the size requested is : %d \n", __func__, size);
	jprobe_return();

	return 0;


}
struct jprobe jp =
{

	.entry = jprobe_kmalloc
};

int ret_handler(struct kretprobe_instance *i, struct pt_regs *regs)
{

	printk(" [%s] kmalloc returns : %lX \n", __func__, regs->ax); // Need to find the proper register
//	printk(" [%s] kmalloc returns \n",__func__ );
	return 0;

}
struct kretprobe krp = 
{

	.handler = ret_handler,
	.maxactive = 20

};

static int __init Init(void)
{

	jp.kp.addr = krp.kp.addr = kallsyms_lookup_name("__kmalloc");
	if(register_jprobe(&jp) < 0)
	{

		printk(" Failed to return the jprobe\n");
		return -1;

	}

	if(register_kretprobe(&krp) < 0)
	{

		printk(" Failed to register the Kprobe\n");
		return -1;

	}

	printk("Plantd the jprobe at the address %p \n", jp.kp.addr);
	return 0;

}

static void __exit Exit(void)
{

	unregister_kretprobe(&krp);
	unregister_jprobe(&jp);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
