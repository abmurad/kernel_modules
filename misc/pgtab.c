#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/highmem.h>
#include <linux/pfn.h>
#include <linux/fs.h>
#include <asm/pgtable_types.h>
#include <linux/sched/signal.h>

#define GPF_DISABLE write_cr0(read_cr0() & (~ 0x10000))
#define GPF_ENABLE write_cr0(read_cr0() | 0x00010000)


static struct task_struct *to_task_struct(char *comm)
{
    struct task_struct *tsk;
    for_each_process(tsk) {
        if (!strcmp(tsk->comm, comm))
            return tsk;
    }
    return 0;
}


/* 2level 10 + 10 + 12 = 32 */
static int __init pgtable_test_init(void)
{
	struct task_struct *task = to_task_struct("getchar");
	
	unsigned long addr = 0x601068;

	struct page *page = NULL;

	//printk("address is %lx ", address);
	
	pgd_t *pgd = pgd_offset(task->mm, addr);

	unsigned long pfn;

	GPF_DISABLE	;
	//pr_info("addr: %lx %lx pgd: %lx pte: %lx\n", pgd_offset(task->mm, addr),(task -> mm -> pgd+( addr >> 22 )) , pgd_index(addr), pte_index(addr));
	pr_info("pgd: %lx\n", pgd->pgd);
	if (!pgd_none(*pgd)) {
		pud_t *pud = pud_offset(pgd, addr);
		if (!pud_none(*pud)) {
			pmd_t *pmd = pmd_offset(pud, addr);
			if (!pmd_none(*pmd)) {
				pte_t *pte = pte_offset_map(pmd, addr);
				//if ((pgd_t *)pud == pgd)
					//pr_info("pud is same as pgd\n");
				//if ((pgd_t *)pmd == pgd)
					//pr_info("pmd is same as pgd\n");
				int *ptr = (pte->pte)+0x68;
				pr_info("pte: %lx\n", *(ptr));
				if (pte_present(*pte)) {
					page = pte_page(*pte);
					pfn = page_to_pfn(page);
					pr_info("pfn: %lx\n", pfn);
				}
				pte_unmap(pte);
			}
		}
	}

	GPF_ENABLE;
	return 0;
}

static void __exit pgtable_test_exit(void)
{
}

module_init(pgtable_test_init);
module_exit(pgtable_test_exit);
