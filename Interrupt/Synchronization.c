#if 0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>

struct task_struct *task[2];

int Task(void *p)
{
	printk(" This is from the thread \n");
	return 0;
}
static int __init Init(void)
{

	task[0] = kthread_create(Task, NULL, "Thread");
	task[1] = kthread_create(Task, NULL, "Thread");

	wake_up_process(task[0]);
	wake_up_process(task[1]);
	return 0;
}

static void __exit Exit(void)
{
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
#endif



#if 0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/mutex.h>

struct task_struct *task[2];

struct mutex mutex;
int Task1(void *p)
{
	mutex_lock(&mutex);
// Once the thread acquires the mutex lock and exit, the acquired mutex can't be released, Even after the module is removed, still we can see the traces of the Thread.
	printk(" %s \n", __func__);
//	mutex_unlock(&mutex);

	return 0;
}

int Task2(void *p)
{
	mutex_lock(&mutex);
	printk(" %s \n", __func__);
	mutex_unlock(&mutex);
	return 0;	
}
static int __init Init(void)
{

	task[0] = kthread_create(Task1, NULL, "Thread1");
	task[1] = kthread_create(Task2, NULL, "Thread2");

	mutex_init(&mutex);

	wake_up_process(task[0]);
	msleep(1000);
	wake_up_process(task[1]);

	return 0;
}

static void __exit Exit(void)
{
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
#endif

#if 0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/mutex.h>

struct task_struct *task[2];
DEFINE_SPINLOCK(spinlock);

int Task1(void *p)
{
	spin_lock(&spinlock); // We can't exit while holding the spin lock also.
//	msleep(1000);// This will give us the scheduling while atomic bug.
//	spin_unlock(&spinlock);
	return 0;
}

int Task2(void *p)
{
	spin_lock(&spinlock);
	spin_unlock(&spinlock);
	return 0;	
}
static int __init Init(void)
{

	task[0] = kthread_create(Task1, NULL, "Thread1");
	task[1] = kthread_create(Task2, NULL, "Thread2");

//	spin_lock_init(&spinlock);

	wake_up_process(task[0]);
	wake_up_process(task[1]);

	return 0;
}

static void __exit Exit(void)
{
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
#endif


#if 0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/mutex.h>

struct task_struct *task[2];
DEFINE_RWLOCK(rwlock);

int Task1(void *p)
{
	read_lock(&rwlock);
	msleep(1000);// This will give us the scheduling while atomic bug. And the sleeping here SPIN when going with the write_lock() with the other process. on the Uniprocessor Machine.
	printk(" %s \n", __func__);
	read_unlock(&rwlock);
	return 0;
}

int Task2(void *p)
{
	write_lock(&rwlock);
//	read_lock(&rwlock);
	printk(" %s \n", __func__);
//	read_unlock(&rwlock);
	write_unlock(&rwlock);
	return 0;	
}
static int __init Init(void)
{

	task[0] = kthread_create(Task1, NULL, "Thread1");
	task[1] = kthread_create(Task2, NULL, "Thread2");


	wake_up_process(task[0]);
	wake_up_process(task[1]);

	return 0;
}

static void __exit Exit(void)
{
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
#endif

#if 0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/semaphore.h>

struct task_struct *task[2];

struct semaphore sem;
int Task1(void *p)
{
	down(&sem);
	down(&sem);
	down(&sem);
		msleep(1000);
		printk(" %s \n", __func__);
	return 0;
}

int Task2(void *p)
{
	msleep(1000);
	up(&sem);
		printk(" %s \n", __func__);
		
	return 0;	
}
static int __init Init(void)
{

	task[0] = kthread_create(Task1, NULL, "Thread1");
	task[1] = kthread_create(Task2, NULL, "Thread2");

sema_init(sem, 1);

	wake_up_process(task[0]);
	wake_up_process(task[1]);

	return 0;
}

static void __exit Exit(void)
{
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
#endif

#if 0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/kthread.h>
struct task_struct *task;

int Thr1(void *p)
{

//	set_current_state(TASK_UNINTERRUPTIBLE);
	task->state = TASK_UNINTERRUPTIBLE;
	schedule();
	printk(" In %s \n", __func__);
	return 0;

}
static int __init Init(void)
{

	task = kthread_create(Thr1, NULL, "Thr1");

	wake_up_process(task);

	return 0;

}

static void __exit Exit(void)
{

	wake_up_process(task);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");

#endif

#if 1

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/preempt.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/preempt.h>
#include <linux/kthread.h>



struct task_struct *task;

int Thr1(void *p)
{

//preempt_disable();

//msleep(1000);
while(1);
printk(" %s \n", __func__);

//preempt_enable();

return 0;
}
static int __init Init(void)
{

	task = kthread_create(Thr1, NULL, "Thr");

	wake_up_process(task);

	return 0;

}

static void __exit Exit(void)
{
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");

#endif
