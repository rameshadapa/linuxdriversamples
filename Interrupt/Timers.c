#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/kthread.h>
#include <linux/delay.h>

struct task_struct *task;
struct timer_list timer;
int flag = 0;

void Timer(unsigned long data)
{
	printk(" Data Received : %lu \n", data);
/*	del_timer(&timer); // Make sure the timer is deleted from the list. But If the timer is already running, it will ensure not to run next tiem untill some one else again adds the timer..
	printk(" WIll this be printed \n");
*/

/*	if(!flag)
	{
		flag ^= 1;
		mod_timer(&timer, jiffies + 10*HZ);
	}
*/
	mod_timer(&timer, jiffies + 10*HZ);
	printk(" This is after modification of the timer.\n");
}

int Thread(void *p)
{

	init_timer(&timer);
	
	timer.expires = jiffies + 2*HZ;
	timer.data    = 10;
	timer.function = Timer;

	add_timer(&timer);
	add_timer(&timer);// Adding two timers is a problem.

	return 0;

}

static int __init Init(void)
{

	task = kthread_create(Thread, NULL, "Kthread");
	wake_up_process(task);
	return 0;

}

static void __exit Exit(void)
{
	del_timer_sync(&timer);
	printk(" Modules is removed\n");
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
