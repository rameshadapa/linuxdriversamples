#if 0
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>

#include <linux/delay.h>

int irq = 1;
static int count = 0;
irqreturn_t Handler(int irq, void *p)
{ // Yes. We can sleep in the Handler.
	printk(" %d ", count);
	printk(" %s \n", __func__);
	msleep(1000); // Here is fine as it is threaded.
/*	if(in_irq())
	   printk("In the Hard IRQ\n");
	if(in_softirq())
	   printk("In the soft IRQ\n");
*/
	return IRQ_HANDLED;
}

irqreturn_t Check_Handler(int irq, void *p)
{

	printk(" %s \n", __func__);
//        msleep(1000);// SLeeping here SUCKS.
	++count;
/*	if(in_irq())
	   printk("In the Hard IRQ\n");
	if(in_softirq())
	   printk("In the soft IRQ\n");
  */      
//	return IRQ_HANDLED;
//	return IRQ_WAKE_THREAD ;
	return IRQ_NONE;
//        return IRQ_NEEDS_HANDLING; // This is not present.


}
static int __init Init(void)
{
//	if(request_threaded_irq(irq, Check_Handler, Handler, IRQF_SHARED, "ctr_handler1", Handler) < 0)
	if(request_threaded_irq(irq, NULL, Handler, IRQF_SHARED, "ctr_handler1", Handler) < 0)
	{
		printk(" Failed to register the interrupt handler \n");
		return -1;
	}

	return 0;
}

static void __exit Exit(void)
{
	free_irq(irq, Handler);
	printk(" %s \n", __func__);
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
#endif

#if 1
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>

#include <linux/slab.h>
#include <linux/atomic.h>

int irq = 1;

struct tasklet_struct *Task;
irqreturn_t Handler(int irq, void *p)
{
	printk(" %s \n", __func__);
/*
	if(in_irq())
	   printk("In the Hard IRQ\n");
	if(in_softirq())
	   printk("In the soft IRQ\n");
*/
	tasklet_schedule(Task); // Rescheduling sucks even with tasklet_kill, tasklet_disable and both.
	return IRQ_HANDLED;
}

void Tasklet_Handler(unsigned long data)
{
	printk(" %s \n", __func__);
	
//	tasklet_schedule(Task);
}

static int __init Init(void)
{
	//if(request_threaded_irq(irq, NULL, Handler, IRQF_SHARED, "ctr_handler1", Handler) < 0)
	Task = kmalloc(sizeof(struct tasklet_struct), GFP_KERNEL);
        Task->next = NULL;
	Task->state = 0;
	Task->count.counter = 0;
	Task->func = Tasklet_Handler;
        Task->data = (unsigned long)irq;

	if(request_irq(irq, Handler, IRQF_SHARED, "ctr_handler1", Handler) < 0)
	{
		printk(" Failed to register the interrupt handler \n");
		return -1;
	}

	return 0;
}

static void __exit Exit(void)
{
//	tasklet_disable(Task); //The below two will make he tasklet to block when the self scheduling of the tasklet
	tasklet_kill(Task);
	free_irq(irq, Handler);
	printk(" %s \n", __func__);
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
#endif
