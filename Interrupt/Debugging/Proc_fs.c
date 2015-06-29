#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>

struct proc_dir_entry *pdir = NULL;
#define PROC_NAME "dummyproc"

int Procread(char *buf, char **start, off_t offset, int count, int *eof, void *data)
{
	int len = 0;
	printk(" Count = %d \n", count);

	*start = 10;

	len += sprintf(buf, "This is printing for the first time \n");
	len += sprintf(buf + len, "This is worse..... \n");


	*eof = 1;	
	
	return len -11;

}

static int __init Init(void)
{

	pdir = create_proc_entry(PROC_NAME, 0644, NULL);
	if(!pdir)
	{
		printk(" Failed to create the %s Proc entry\n", PROC_NAME);

		remove_proc_entry(PROC_NAME, NULL);
		return -ENOMEM;

	}

	pdir->read_proc = Procread;
	pdir->write_proc = NULL;
	pdir->mode = S_IFREG | S_IRUGO;
	pdir->uid = 0;
	pdir->gid = 0;
	pdir->size = 37;

	printk(" proc entry %s is created \n", PROC_NAME);

	return 0;


}

static void __exit Exit(void)
{

	printk(" %s \n",  __func__);
	remove_proc_entry(PROC_NAME, NULL);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
