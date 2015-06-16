#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/scatterlist.h>
#include <linux/slab.h>

struct scatterlist *sgl;
struct page *page = NULL;
#define NENTS 10
static int __init Init(void)
{
	int i;
	sgl = kmalloc(NENTS * sizeof(*sgl), GFP_KERNEL);
	if(!sgl) return -ENOMEM;

	sg_init_table(sgl, NENTS);

	for(i=0; i<NENTS; ++i)
	{

		page = alloc_page(GFP_KERNEL);
		sg_set_page(sg, page, 256, 0);

	}


	dma+map_sg(sg, 


}

static void __exit Exit(void)
{
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
