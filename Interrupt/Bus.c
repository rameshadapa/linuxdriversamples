#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>


static int Match(struct device *dev, struct device_driver *drv)
{
	printk(" %s \n", __func__);
	return 1;

}

static int Uevent(struct device *dev, struct kobj_uevent_env *env)
{

	printk(" %s \n", __func__);
	return 0;

}

struct bus_type ctr_bus =
{

	.name = "CTRBUS",
	.match = Match,
	.uevent = Uevent

};

void DEVRelease(struct device *dev)
{
}

struct device dev[] =
{

     {
	.bus = &ctr_bus,
	.init_name = "Device1",
	.release = DEVRelease
     },

     {
	.bus = &ctr_bus,
	.init_name = "Device20",
	.release = DEVRelease
     }
};

struct device_driver drv = 
{

	.name = "Driver1",
	.bus = &ctr_bus

};

static int __init Init(void)
{

	bus_register(&ctr_bus);
	device_register(&dev[0]);
//	device_register(&dev[1]);
//	driver_register(&drv);

	printk(" %s \n", __func__);
	return 0;
	

}

static void __exit Exit(void)
{

//	driver_unregister(&drv);
//	device_unregister(&dev[1]);
	device_unregister(&dev[0]);
	bus_unregister(&ctr_bus);

	printk(" %s \n", __func__);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
