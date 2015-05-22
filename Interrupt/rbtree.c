#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rbtree.h>

#define LENGTH(a) (sizeof(a)/sizeof(a[0]))

struct rb_root rb_root = RB_ROOT;
struct data
{
	int ele;
	struct rb_node node;
}O[8] = {{7}, {3}, {5}, {8}, {6}, {1},{11}, {0}};

void Search_RB_Tree(struct rb_root *root, int ele)
{

	struct rb_node *node = root->rb_node;
	while(node)
	{
		struct data *p = rb_entry(node, struct data, node);
		if(ele < p->ele )
			node = node->rb_left;
		else if(ele > p->ele)
			node = node->rb_right;
		else
		    {	printk(" Element is found : %d \n", ele); return;}
	}

	printk(" Element is not found\n");
	return;

}
static int __init Init(void)
{

	int n = LENGTH(O), i;

	//RB Insertion.
	for(i=0; i<n; ++i)
	{
		struct rb_node **link = &(rb_root.rb_node), *parent = NULL;
		struct data *p = NULL;
		while(*link)
		{
			parent = *link;
			p = rb_entry(*link, struct data, node);
			if(O[i].ele < p->ele)
				link = &((*link)->rb_left);
			else 
				link = &((*link)->rb_right);
			
		}
		
		rb_link_node(&O[i].node, parent, link);
		rb_insert_color(&O[i].node, &rb_root);
	}


	struct rb_node *node;
	//for(node = rb_first(&rb_root); node; node = rb_next(node))
	for(node = rb_last(&rb_root); node; node = rb_prev(node))
		printk(" %d \n", rb_entry(node, struct data, node)->ele);

	Search_RB_Tree(&rb_root, 10);
	Search_RB_Tree(&rb_root, 11);
	Search_RB_Tree(&rb_root, 5);
	Search_RB_Tree(&rb_root, 6);
	Search_RB_Tree(&rb_root, 2);
	
	return 0;

}

static void __exit Exit(void)
{
	printk(" %s \n", __func__);
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
