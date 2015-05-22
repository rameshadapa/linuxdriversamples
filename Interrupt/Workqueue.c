#if 0
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/jiffies.h>

int irq = 1;
static int counter_int, counter_work;
struct work_struct work;

void func(void *data)
{

        msleep(1000);
	printk(" %s[%d] \n", __func__,++counter_work);

}
//DECLARE_WORK(work, func);
DECLARE_DELAYED_WORK(d_work, func);
irqreturn_t Handler(int irq, void *p)
{
	printk(" %s[%d] \n", __func__, ++counter_int);
	
//        schedule_work(&work);
        schedule_delayed_work(&d_work,  2*HZ);
	return IRQ_HANDLED;
	
}

static int __init Init(void)
{

	if(request_irq(irq, Handler, IRQF_SHARED, "Ctr_Int", &Handler) < 0)
	{
		printk(" Failed to register the interrupt \n");
		return -1;
	}

//INIT_WORK(&work, func);
	return 0;
}

static void __exit Exit(void)
{
	free_irq(irq, Handler);
	flush_scheduled_work();	
	cancel_delayed_work(&d_work);
	printk(" Module is removed \n");

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
#endif

#if 1
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/jiffies.h>

int irq = 1;
static int counter_int, counter_work;
struct work_struct work;
struct workqueue_struct *wq;

void func(void *data)
{

        msleep(1000);
	printk(" %s[%d] \n", __func__,++counter_work);

}
DECLARE_WORK(work, func);
DECLARE_DELAYED_WORK(d_work, func);
irqreturn_t Handler(int irq, void *p)
{
	printk(" %s[%d] \n", __func__, ++counter_int);
	
      queue_work(wq, &work);
      queue_delayed_work(wq, &d_work,  2*HZ);
	return IRQ_HANDLED;
	
}

static int __init Init(void)
{

	if(request_irq(irq, Handler, IRQF_SHARED, "Ctr_Int", &Handler) < 0)
	{
		printk(" Failed to register the interrupt \n");
		return -1;
	}

	wq = create_singlethread_workqueue("ctr-qorkQueue");
//INIT_WORK(&work, func);
	return 0;
}

static void __exit Exit(void)
{
	free_irq(irq, Handler);
	flush_workqueue(wq);	
	cancel_delayed_work(&d_work);
	printk(" Module is removed \n");

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
#endif
