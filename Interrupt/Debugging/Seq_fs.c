#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/string.h>

#define PROC_NAME "dummyctr"

struct proc_dir_entry *dir = NULL;

static void* Start(struct seq_file *seq_file, loff_t *pos)
{

	printk(" %s \n", __func__);

	if(*pos == 0)
	{
		return !NULL;
	}
	else
	{
		return NULL;
	}

}

static void *Next(struct seq_file *file, void *data, loff_t *pos)
{

	
	printk(" %s \n", __func__);
	if(*pos == 0) 
	{
		*pos = 1;
		return pos;
	}
	else
	  return NULL;

}

static void Stop(struct seq_file *file, void *v)
{
	printk(" %s \n", __func__);
}

static  int Show(struct seq_file *sfile, void *v)
{

	printk(" %s \n", __func__);
	char buf[4096];
	int i;
	for(i=0; i<4094; ++i) buf[i] = (i%127) + 1;

	buf[4094] = '\0'; 
	
	//seq_printf(sfile, "The is returned \n");
	seq_printf(sfile,"%s\n", buf);
	printk(" File Size %d  && File count : %d \n", sfile->size, sfile->count);
	
	return 0;	
}

struct seq_operations seq_ops = 
{

	.start = Start,
	.next  = Next,
	.stop  = Stop,
	.show  = Show

};
static int SeqOpen(struct inode *inode, struct file *filp)
{

	printk(" %s \n", __func__);
	return seq_open(filp, &seq_ops);

}
struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = SeqOpen,
	.read = seq_read,
	.release = seq_release,
	.llseek = seq_lseek

};
static int __init Init(void)
{

	dir = create_proc_entry(PROC_NAME, 0666, NULL);
	if(dir)
		dir->proc_fops = &fops;

	return 0;

}

static void __exit Exit(void)
{

	printk(" %s \n", __func__);
	remove_proc_entry(PROC_NAME, NULL);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");

/*


[  238.325938]  SeqOpen 
[  238.325974]  Start 
[  238.325976]  Show 
[  238.325979]  Next 
[  238.325980]  Show 
[  238.325982]  Next 
[  238.325983]  Stop 
[  238.326028]  Start 
[  238.326030]  Stop 

//For : buf[4094] = '\0';
[ 2554.436538]  Start 
[ 2554.436541]  Show 
[ 2554.436570]  File Size 4096  && File count : 4095 
[ 2554.436572]  Next 
[ 2554.436574]  Show 
[ 2554.436602]  File Size 4096  && File count : 4096 
[ 2554.436604]  Stop 
[ 2554.438636]  Start 
[ 2554.438639]  Stop 
[ 2561.418607]  Exit 



For : buf[4095] = '\0';
[ 2460.429335]  Stop 
[ 2460.429344]  Start 
[ 2460.429346]  Show 
[ 2460.429374]  File Size 8192  && File count : 4096 
[ 2460.429376]  Next 
[ 2460.429377]  Show 
[ 2460.429406]  File Size 8192  && File count : 8192 
[ 2460.429407]  Stop 
[ 2460.433361]  Start 
[ 2460.433365]  Stop 
*/
