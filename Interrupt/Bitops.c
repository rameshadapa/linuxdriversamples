#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/bitops.h>


unsigned long word = 0;

static int __init Init(void)
{

set_bit(0, &word);
set_bit(1, &word);
printk(" %lu \n", word); //3
printk(" %lu \n", test_and_set_bit(2, &word));//0
printk(" %lu \n", test_and_set_bit(3, &word));//0
printk(" %lu \n", test_and_set_bit(4, &word));//0
printk("Val: %lu \n", word); //3
printk(" %lx \n", test_and_clear_bit(4, &word));//0xFFFFFFFF
printk("Val: %lu \n", word); //3

return 0;
}

static void __exit Exit(void)
{

printk(" %s \n", __func__);

}

module_init(Init);
module_exit(Exit);
MODULE_LICENSE("GPL");
/*
[35194.843320]  3 
[35194.843321]  0 
[35194.843322]  0 
[35194.843323]  0 
[35194.843323] Val: 31 
[35194.843324]  ffffffff 
[35194.843325] Val: 15 

*/
