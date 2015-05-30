#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>

struct fake_device {
	char data[100];
	struct semaphore sem;
} virtual_device;

#define DEVICE_NAME	"chardev"
struct cdev *mcdev;
static int major_num;
dev_t dev_num;
ssize_t	ret;

int device_open(struct inode *inode, struct file *filep)
{
	if(down_interruptible(&virtual_device.sem) != 0)
	{
		printk("<1>chardev: could not lock device during open.\n");
		return -1;
	}
	printk("<1>chardev: open device.\n");
	return 0;
}

ssize_t device_read(struct file* filep, char* buff, size_t size, loff_t *off)
{
	printk("<1>chardev: reading from device.\n");
	ret = copy_to_user(buff, virtual_device.data, size);
	return ret;
}

ssize_t device_write(struct file* filep, const char* buff, size_t size, loff_t *off)
{
	printk("<1>chardev: writing to device.\n");
	ret = copy_from_user(virtual_device.data, buff, size);
	return ret;
}

int device_close(struct inode *inode, struct file *filep)
{
	up(&virtual_device.sem);
	printk("<>chardev: closed device.\n");
	return 0;
}

struct file_operations fops = {
	.owner	= THIS_MODULE,
	.open	= device_open,
	.release = device_close,
	.write	= device_write,
	.read	= device_read
};

static int __init char_dev_sample_init(void)
{
	ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
	if(ret < 0) {
		printk("<1>chardev: failed to allocate the major number.");
		return ret;
	}
	major_num = MAJOR(dev_num);
	printk("<1>chardev: major number is: %d\n", major_num);
	printk("<1>use \"mknod /dev/%s c %d 0\" for device file\n", DEVICE_NAME, major_num);

	mcdev = cdev_alloc();
	mcdev->ops = &fops;
	mcdev->owner = THIS_MODULE;

	ret = cdev_add(mcdev, dev_num, 1);

	if(ret < 0) {
		printk("<1>chardev: unable to add cdev to kernel.\n");
		return ret;
	}

	sema_init(&virtual_device.sem, 1);

	return 0;
}

static void __exit char_dev_sample_exit(void)
{
	cdev_del(mcdev);
	unregister_chrdev_region(dev_num, 1);
	printk("<1>chardev: unloaded device.");
}


module_init(char_dev_sample_init);
module_exit(char_dev_sample_exit);
