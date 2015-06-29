#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/debugfs.h>

struct dentry *dentry = NULL;
u32 sum = 0;

static int write_op(void *data, u64 value)
{

	sum += value;
	return 0;

}

DEFINE_SIMPLE_ATTRIBUTE(fops, NULL, write_op, "%llu\n");
static int __init Init(void)
{

	dentry = debugfs_create_dir("CTR", NULL);
	if(!dentry)
	{
		printk(" Debugfs is failed to create \n");
		return -ENODEV;

	}


	debugfs_create_file("ctr_file", 0666, dentry, NULL, &fops);
	debugfs_create_u32("res_ctr_file", 0666, dentry, &sum);

	return 0;

}

static void __exit Exit(void)
{


	debugfs_remove_recursive(dentry);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
