#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/semaphore.h>
#include <linux/sched.h>
#include <linux/uaccess.h>



struct generic_device  
{

	wait_queue_head_t inq, outq;
	struct fasync_struct *fa;
	struct semaphore sem;
	char *rp, *wp;
	int buffer_size;
	char *buffer, *end;
	struct cdev cdev;
	struct class *cl;
	dev_t dev;
	
};



static int Open(struct inode *inode, struct file *filp)
{


	struct generic_device *dev = container_of(inode->i_cdev, struct generic_device, cdev);
	if(!dev) return -EFAULT;

	printk(" %s \n", __func__);
	filp->private_data = dev;
	return nonseekable_open(inode, filp);

}

static int Close(struct inode *inode, struct file *filp)
{
	struct generic_device *dev = filp->private_data;
/*
	if(dev) 
	{
		
		kfree(dev->buffer);
		kfree(dev);
		filp->private_data = NULL;
	}
*/
	printk(" %s \n", __func__);
	return 0;
}

static int Read(struct file *filp, char __user *buf, size_t count, loff_t *off)
{

	struct generic_device *dev = filp->private_data;
	if(!dev) return -ENOTTY;

	if(down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	while(dev->rp == dev->wp)// This while loop is necessary as the different process might wait on the same wait queue at the different place of the driver , and if one process calls the wake_up_interruptible(), all the process on the wait queue will wake up even though the condition is false.
	{// Data is not yet ready.
		up(&dev->sem);

		//Check if the file is opened in O_NONBLOCK mode, so, that we can return -EAGAIN.
		if(filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		//Lets sleep untill the data is ready as it is opened in blocking mode.
		if(wait_event_interruptible(dev->inq, dev->rp != dev->wp))
			return -ERESTARTSYS;

		if(down_interruptible(&dev->sem)) 
			return -ERESTARTSYS;
	}


	//Now read the data as it is ready to read.
	if(dev->wp > dev->rp)
		count = min(count, (size_t)(dev->wp - dev->rp));
	else // dev->wp is wrapped up
		count = min(count, (size_t)(dev->end - dev->rp));

	if(copy_to_user(buf, dev->rp, count))
	{
		up(&dev->sem);
		return -EFAULT;
	}

	dev->rp += count;
	printk(" %d bytes are read from function %s of process  %s \n", count, __func__, current->comm);
	if(dev->rp == dev->end)// Wrap up the pointer. 
		dev->rp = dev->buffer;
	up(&dev->sem);

	wake_up_interruptible(&dev->outq);



	return count;
}

int spacefree(struct generic_device *dev)
{

	if(dev->rp == dev->wp) return dev->buffer_size -1;

	return ((dev->rp + dev->buffer_size - dev->wp) % dev->buffer_size) - 1;

}

int get_write_space(struct generic_device *dev, struct file *filp)
{

	while(spacefree(dev) == 0)
	{
		DEFINE_WAIT(wait);
		up(&dev->sem);

		if(filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		prepare_to_wait(&dev->outq, &wait, TASK_INTERRUPTIBLE);
		if(spacefree(dev) == 0)
			schedule();
		finish_wait(&dev->outq, &wait);
		if (signal_pending(current))
			return -ERESTARTSYS;
		if(down_interruptible(&dev->sem))
			return -ERESTARTSYS;
	}
	return 0;

}

static int Write(struct file *filp, const char __user *buf, size_t count, loff_t *pos)
{
	int result;
	struct generic_device *dev = filp->private_data;

	if(down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	result = get_write_space(dev, filp);
	if(result) return result;

	// Space is present.
	count = min(count, (size_t) spacefree(dev));
	if(dev->wp > dev->rp)
		count = min(count, (size_t)(dev->end - dev->wp));
	else // The pointer is wrapped up
		count = min(count, (size_t)(dev->rp - dev->wp -1));

	if(copy_from_user(dev->wp, buf, count))
	{
		up(&dev->sem);
		return -EFAULT;
	}

	dev->wp += count;
	printk(" %d bytes are written from function %s of process  %s \n", count, __func__, current->comm);

	if(dev->wp == dev->end)
		dev->wp = dev->buffer;
	up(&dev->sem);

	//Wake up for any writers.
	wake_up_interruptible(&dev->inq);


	if(dev->fa)
		kill_fasync(&dev->fa, SIGIO, POLL_IN);

	return count;	
}

static int Fasync(int fd, struct file *filp, int mode)
{

	struct generic_device *dev = filp->private_data;
	printk(" %s \n", __func__);

	return fasync_helper(fd, filp, mode, &dev->fa);
}

struct file_operations fops =
{

	.owner   = THIS_MODULE,
	.open    = Open,
	.read    = Read,
	.write   = Write,
	.release = Close,
//	.poll    = Poll,
	.fasync  = Fasync
};

struct generic_device *gdevice = NULL;
static int __init Init(void)
{
	gdevice = kmalloc(sizeof(*gdevice), GFP_KERNEL);
	if(!gdevice) return -ENOMEM;

	alloc_chrdev_region(&gdevice->dev, 0, 1, "DEV");
	gdevice->cl = class_create(THIS_MODULE, "ctrclass");
	device_create(gdevice->cl, NULL, gdevice->dev, NULL, "comp");
	cdev_init(&gdevice->cdev, &fops);
	cdev_add(&gdevice->cdev, gdevice->dev, 1);

	
	sema_init(&gdevice->sem, 1);
	init_waitqueue_head(&gdevice->inq);
	init_waitqueue_head(&gdevice->outq);
	gdevice->buffer_size = 10;
	gdevice->buffer      = kmalloc(gdevice->buffer_size, GFP_KERNEL);
	gdevice->end         = gdevice->buffer + gdevice->buffer_size;
	gdevice->rp = gdevice->wp = gdevice->buffer;
	gdevice->fa = NULL;


	printk(" %s \n",__func__);	
	return 0;
}

static void __exit Exit(void)
{

	printk(" %s \n",__func__);	
	cdev_del(&gdevice->cdev);
	device_destroy(gdevice->cl, gdevice->dev);	
	class_destroy(gdevice->cl);
	unregister_chrdev_region(gdevice->dev, 1);

	kfree(gdevice->buffer);
	kfree(gdevice);
	gdevice = NULL;

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
