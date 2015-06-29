#if 0
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <asm/page.h>

struct page *page = NULL;
pg_data_t *node = NODE_DATA(0);
static int __init Init(void)
{

	page = alloc_page(GFP_KERNEL);

	printk(" Page : %X \n", page);
//	printk(" virtual : %X \n", page->virtual);
	printk(" PFN     : %X \n", page_to_pfn(page));
	printk(" Phys    : %X \n", page_to_phys(page));
	printk(" memmap = %X \n", mem_map);
	printk(" Calculated PFN : %X \n", page - (struct page*) mem_map);
	printk(" Actual base : %X \n", node->node_mem_map);
	printk(" Offset : %X \n", (unsigned long)node->node_mem_map - (unsigned long)mem_map);
	printk(" Node start PFN : %X \n", node->node_start_pfn);
//	printk(" Virt    : %X \n", page_to_virt(page));
	
	__free_pages(page, 0);

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
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mm.h>


static int __init Init(void)
{

struct page *page = NULL;
page = alloc_pages(GFP_KERNEL, 9);
if(!page) printk(" Failed to allocate the page memory \n");

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
#include <linux/mm.h>
#include <linux/slab.h>

struct kmem_cache *cache = NULL;

void ctor(void *p)
{

	printk(" %s \n", __func__);

}
static int __init Init(void)
{

	char *p;
	cache = kmem_cache_create("ctr-cache", 4097, 0, SLAB_CACHE_DMA | SLAB_PANIC, ctor);

	p = kmem_cache_alloc(cache, GFP_KERNEL);
	if(!p)
		printk(" Failed to allocate the cache \n");

	kmem_cache_free(cache, p);
	
	return 0;
}

static void __exit Exit(void)
{

	kmem_cache_destroy(cache);
}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");

#endif
