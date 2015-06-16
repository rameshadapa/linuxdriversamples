#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/scatterlist.h>
#include <linux/mm.h>
#include <linux/slab.h>

void *p;
static int __init Init(void)
{

//	p = vmalloc(95*1024*1024);

	p = kmalloc(4194304, GFP_KERNEL);
	if(!p)
	{

		printk(" Failed to allocate the Vmalloc()\n");
		return -1;
	}
	
	BUG_ON(1);

	return 0;

}

static void __exit Exit(void)
{

	kfree(p);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
