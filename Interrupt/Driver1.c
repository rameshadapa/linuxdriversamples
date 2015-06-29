#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/sched.h>

int irq = 1;
int ctr_var= 0;
irqreturn_t Ctr_handler (int n, void *p)
{
	printk("The handler is called \n");
//	++ctr_var;
//	schedule();
	return IRQ_HANDLED;
}

static int __init Init(void)
{
	if(request_irq(irq, Ctr_handler, IRQF_SHARED, "ctrInterrupt", &irq) < 0)
		{
			printk("Faiuled to register the Interrupt handler\n");
			return -1;			
		}
	printk("Handler is registered\n");
	return 0;
}


static void __exit Exit(void)
{
	free_irq(irq, &irq);
}


module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL"); 
