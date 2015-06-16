#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/fs.h>


dev_t dev;
struct class *cl;
static int __init Init(void)
{

	alloc_chrdev_region(&dev, 0, 1, "DEV");
	cl = class_create(THIS_MODULE, "Ctr_Class");
	device_create(cl, NULL, dev, NULL, "Dummy");

	return 0;


}

static void __exit Exit(void)
{

	device_destroy(cl, dev);
	class_destroy(cl);
	unregister_chrdev_region(dev, 1);

	printk(" %s \n", __func__);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
