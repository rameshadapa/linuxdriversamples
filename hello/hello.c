/** hello.c **/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init hello_init(void)
{
 	printk("Entering into beautiful world.\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk("Exiting from the cruel world.\n");
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello Module");
MODULE_AUTHOR("Ramesh Adapa (ramesh.adapa86@gmail.com)");
