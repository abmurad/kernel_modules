#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/kdebug.h>

#if 0
struct die_args {
    struct pt_regs *regs;
    const char *str;
    long err;
    int trapnr;
    int signr;
};  


#endif

int (test_func)(struct notifier_block *nb,
            unsigned long action, void *data)
{
	printk (" __UMA__ %s %s %d\n",__FILE__,__func__,__LINE__); 
}
#if 0
struct notifier_block {
    notifier_fn_t notifier_call;
    struct notifier_block __rcu *next;
    int priority;
};

#endif
struct notifier_block nb ;
int init_module(void)
{
	nb.notifier_call = test_func ;
	register_die_notifier(&nb);	
	int *q = 0;
	*q = 1 ;

#if 0		
		printk("pgd = %u pmd = %u pte = %u PAGE_SHIFT = %u PGDIR_SHIFT = %u PMD_SHIFT = %u PUD_SHIFT = %u PAGE_MASK = %lu, PAGE_SIZE = %lu PMD_SIZE = %lu PMD_MASK = %lu PGDIR_MASK = %lu PAGE_SIZE = %lu PUD_MASK = %lx \n",PTRS_PER_PGD,PTRS_PER_PMD,PTRS_PER_PTE,PAGE_SHIFT,PGDIR_SHIFT,PMD_SHIFT,PUD_SHIFT,PAGE_MASK,PAGE_SIZE,PMD_SIZE,PMD_MASK,PGDIR_MASK,PGDIR_SIZE,PUD_MASK);
#endif

		return 0;
}


void cleanup_module(void)
{
		
}  

MODULE_LICENSE("GPL");

