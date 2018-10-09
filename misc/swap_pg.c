#include <linux/init.h>
#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/gfp.h>
#include <linux/kallsyms.h>

static int __init test_init(void)
{
	int i;
	struct page *page = alloc_page(GFP_DMA); //GFP_KERNEL GFP_DMA GFP_DMA32 __GFP_HIGHMEM
	unsigned long va = (unsigned long)page_address(page);
	unsigned long pa = __pa(va);
	unsigned long pfn = page_to_pfn(page);
	int pgd_idx = pgd_index(va);
	int pte_idx = pte_index(va);
	pgd_t *pgdp, *pgd_base = (pgd_t *)kallsyms_lookup_name("swapper_pg_dir");
	if (!pgd_base)
		return 0;
	pgd_t *pgd = pgd_base + pgd_idx;
	pmd_t *pmd = (pmd_t *)pgd;
	pte_t *pte_base = (pte_t *)pmd_page_vaddr(*pmd), *ptep;
	pte_t *pte = pte_offset_kernel(pmd, va);
	pgd_t *pgd_base_user = current->mm->pgd;

	pr_info("pfn=%lx va=%lx pa=%lx\n", pfn, va, pa);
	pr_info("pgd_idx: %x, pte_idx: %x, pgd_base->pgd: %lx, pgd->pgd: %lx, pte->pte: %lx\n",
			pgd_idx, pte_idx, pgd_base->pgd, pgd->pgd, pte->pte);

	for (i = 0x0; i < 0x400; i++) {
		pgdp = pgd_base + i;
		pr_info("pgd_kern[%d]=%lx ", i, pgdp->pgd);
		pgdp = pgd_base_user + i;
		pr_info("pgd_user[%d]=%lx ", i, pgdp->pgd);
	}

	for (i = 0x0; i < 0x400; i++) {
		ptep = pte_base + i;
		pr_info("pte[%d]=%lx ", i, ptep->pte);
		if (ptep == pte)
			pr_info("i = %d matched!, pfn = %d\n", i, pfn);
	}

	return 0; 
}

static void __exit test_exit(void) 
{
} 

module_init(test_init); 
module_exit(test_exit);
MODULE_LICENSE("GPL"); 
