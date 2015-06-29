#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/kprobes.h>

int jprobe_a_jprobe(void *ptr, struct pt_regs *regs)
{

	printk(" This is printing from the %s function and the value is %d \n", __func__, *(int*)ptr);

	*(int*)ptr  = *(int*)ptr + 10;
	dump_stack();
	jprobe_return();

	printk(" [%s][%d] Will this point is reached \n", __func__, __LINE__); // Never
	return 0;

}

static struct jprobe jp =
{

	.entry = jprobe_a_jprobe,

};

static int __init Init(void)
{

	jp.kp.addr = (kprobe_opcode_t *)kallsyms_lookup_name("a_jprobe");
	if(register_jprobe(&jp) < 0)
	{
		printk(" Failed to rgister the Jprobe\n");
		return -1;
	}

	printk(" Planted Jprobe at the address %p \n", jp.kp.addr);
	return 0;


}

static void __exit Exit(void)
{

	printk(" Removed the jprobe handler at the address %p \n", jp.kp.addr);
	unregister_jprobe(&jp);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
