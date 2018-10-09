#include <linux/init.h>
#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/gfp.h>

static int __init test_init(void)
{
	struct page *page;
	unsigned long va, pa, pfn;

       	page = alloc_page(GFP_DMA);
       	pfn = page_to_pfn(page);
        va = (unsigned long)page_address(page);
       	pa = __pa(va);
	pr_info("pfn=%lx va=%lx pa=%lx\n", pfn, va, pa);

	page = alloc_page(__GFP_HIGHMEM);
	pfn = page_to_pfn(page);
	va = (unsigned long)page_address(page);
	pa = __pa(va);
	pr_info("pfn=%lx va=%lx pa=%lx\n", pfn, va, pa);

	return 0; 
}

static void __exit test_exit(void) 
{
} 

module_init(test_init); 
module_exit(test_exit);
MODULE_LICENSE("GPL"); 
