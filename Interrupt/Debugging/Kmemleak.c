#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

static int __init Init(void)
{

	int *a, *b;

	a= kmalloc(1024, GFP_KERNEL);
	b = kmalloc(1024, GFP_KERNEL);

	kfree(b);
	
	return 0;

}

static void __exit Exit(void)
{

	printk(" Exiting the application \n");
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
