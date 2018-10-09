#include <linux/init.h>
#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/gfp.h>

static int __init ptest_init(void)
{
	struct page *page1, *page2, *page = alloc_page(GFP_DMA); //GFP_KERNEL GFP_DMA GFP_DMA32 __GFP_HIGHMEM
	void *addr = kmap_atomic(page);
	unsigned long pa = __pa(addr);
	void *va = __va(pa);
	unsigned long pfn = page_to_pfn(page);
	pr_info("%x mem_map\n" ,&mem_map[pfn]);
//	pr_info("pfn=%ld addr=%p pa=%ld va=%p\n", pfn, addr, pa, va);
	pr_info("pfn=%lx addr=%p pa=%lx va=%p\n", pfn, addr, pa, va);
	pr_info("PAGE_SIZE * pfn = %ld * %ld = %ld -> %lx\n", PAGE_SIZE, pfn, PAGE_SIZE * pfn, PAGE_SIZE * pfn);
	pr_info("PAGE_OFFSET + pa = %lx + %lx = %lx\n", PAGE_OFFSET, pa, PAGE_OFFSET + pa);

	page1 = &mem_map[pfn];
	if (page == page1)
		pr_info("page1 is same as page.\n");

	page2 = mem_map + pfn;
	if (page == page2)
		pr_info("page2 is same as page.\n");

	kunmap_atomic(addr);

	return 0; 
}

static void __exit ptest_exit(void) 
{
} 

module_init(ptest_init); 
module_exit(ptest_exit);

MODULE_LICENSE("GPL"); 
