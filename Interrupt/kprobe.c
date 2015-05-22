#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/kprobes.h>
int pre(struct kprobe *p, struct pt_regs *regs)
{

	printk(" %s \n",__func__);
	return 0;

}

void post(struct kprobe *kp, struct pt_regs *regs, unsigned long flags)
{

	printk(" %s \n",__func__);
	

}

static struct kprobe kp;
static int __init Init(void)
{

kp.pre_handler = pre;
kp.post_handler = post;
kp.addr = (kprobe_opcode_t *)0xf85eb000;
register_kprobe(&kp);
return 0;

}

static void __exit Exit(void)
{

unregister_kprobe(&kp);
printk(" %s \n", __func__);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
