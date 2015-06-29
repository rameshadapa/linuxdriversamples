#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

static int val = 0;

int a_jprobe(void *p)
{

	printk(" In %s printing the value %d \n", __func__, *(int*)p);
	return 0;


}
EXPORT_SYMBOL_GPL(a_jprobe);

static int Open(struct inode *inode, struct file *filp)
{

	printk(" %s \n", __func__);
	return 0;
}

static int Release(struct inode *inode, struct file *filp)
{

	printk(" %s \n", __func__);
	return 0;

}

static int Write(struct file *filp, const char __user *buf, size_t count, loff_t *pos)
{

	++val;
	a_jprobe(&val);
	return 1;
}

struct file_operations fops =
{

	.open  = Open,
	.release = Release,
	.write = Write,
	.owner = THIS_MODULE

};
struct miscdevice mdev =
{

	.minor = MISC_DYNAMIC_MINOR,
	.name  = "probe",
	.fops = &fops

};
static int __init Init(void)
{
	
//	*(unsigned char*)0x0 = 90;
	return misc_register(&mdev);

}

static void __exit Exit(void)
{

	misc_deregister(&mdev);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
