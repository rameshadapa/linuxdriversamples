#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>


static int Open(struct inode *inode, struct file *filp)
{

	printk(" %s \n", __func__);
	return 0;

}

static int Close(struct inode *inode, struct file *filp)
{
	printk(" %s \n", __func__);
	return 0;
}
static struct file_operations fops = 
{

	.open = Open,
	.release = Close

};

struct miscdevice miscdev = 
{

	.minor = MISC_DYNAMIC_MINOR,
	.name = "misc_ctr",
	.fops = &fops
};

static int __init Init(void)
{

	misc_register(&miscdev);
	printk(" Minor is : %d \n", miscdev.minor);
	return 0;

}

static void __exit Exit(void)
{

	misc_deregister(&miscdev);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
