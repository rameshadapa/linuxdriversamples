#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>

struct cdev cdev;
struct class *cl;
dev_t dev;

struct handle 
{

	wait_queue_head_t inq;
	wait_queue_head_t outq;
}handle = 
	{
		.inq  = __WAIT_QUEUE_HEAD_INITIALIZER(handle.inq),
		.outq = __WAIT_QUEUE_HEAD_INITIALIZER(handle.outq) 
	};

static int Open(struct inode *inode, struct file *filp)
{


printk(" Suck %s \n", __func__);
return 0;

}

static int Close(struct inode *inode, struct file *filp)
{

printk(" %s \n", __func__);
return 0;
}

static ssize_t Read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{

printk(" %s \n", __func__);
copy_to_user(buf, "charan", sizeof("charan"));
*(char*)0x0 = 0;
printk(" %s \n","charan");
return 7;
}

static ssize_t Write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{

return 0;
}

static int Fasync(int fd, struct file *filp, int mode)
{

return 0;
}

struct file_operations fops =
{

	.open = Open,
	.read = Read,
	.write = Write,
	.fasync = Fasync,
	.release = Close,

};

static int __init Init(void)
{


	alloc_chrdev_region(&dev, 1, 0, "DEV");
	cl = class_create(THIS_MODULE, "Ctr_Class");
	device_create(cl, NULL, dev, NULL, "fasync");
	cdev_init(&cdev, &fops);
	cdev_add(&cdev, dev, 1);

	return 0;


}

static void __exit Exit(void)
{

	cdev_del(&cdev);
	device_destroy(cl,dev);
	class_destroy(cl);
	unregister_chrdev_region(dev, 1);

	printk(" %s \n", __func__);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
