#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/kthread.h>

struct task_struct *ptr;
static int counter;
EXPORT_SYMBOL(counter);

int Thread1(void *data)
{

	while(counter < 2000)
	{
		++counter;
		msleep(250);
	}

	return 0;

}

static int __init Init(void)
{

	ptr = kthread_create(Thread1, NULL, "Thread1");

	wake_up_process(ptr);

	printk(" %s \n", __func__);
	return 0;
}

static void __exit Exit(void)
{
	kthread_stop(ptr);
	printk(" %s \n", __func__);
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
