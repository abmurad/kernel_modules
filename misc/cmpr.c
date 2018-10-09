#include <linux/init.h>
#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/gfp.h>
#include <linux/kallsyms.h>
#include <linux/pipe_fs_i.h>
#include <linux/fdtable.h>
static struct task_struct *to_task_struct(char *comm)
{
    struct task_struct *tsk;

    for_each_process(tsk) {

//        printk("pgd is %x %x %s\n" , tsk -> mm , tsk -> active_mm , tsk -> comm );

        if (!strcmp(tsk->comm, comm))

          return tsk;
    }

    return 0;
}

static int __init test_init(void)
{
	int i;
	pgd_t *pgdp;

	struct task_struct *inst  = NULL ;

	inst = to_task_struct("someapp");

	if ( !inst ) return -ENOMEM ;

//	while ( inst -> files -> fdt -> fd[i] ) ;

//	printk("%x\n" , inst -> files -> fdt -> fd[i++] -> private_data);

//	struct pipe_inode_info *pipe_inst =  inst -> files -> fdt -> fd[4] ;
	
//	printk("%x %x %x\n" , pipe_inst -> readers , pipe_inst -> writers , pipe_inst -> files);
	
//	printk("%x %s %x\n" , pipe_inst -> nrbufs , pipe_inst -> curbuf , pipe_inst -> buffers ) ;
	
//	printk("%x %x \n" , pipe_inst -> r_counter , pipe_inst -> w_counter) ;

//	printk ("%x\n" , pipe_inst -> user );

/*	printk("%d\n" , inst -> pid);
inst -> files -> fdt -> fd[0]
	pgd_t *pgd_base_kern = (pgd_t *)kallsyms_lookup_name("swapper_pg_dir");
	pgd_t *pgd_base_user = inst->mm->pgd;
	
	//printk("%d %s\n" , current -> pid , current -> comm );

	for (i = 0x0; i < 0x400; i++) {
		pgdp = pgd_base_kern + i;
		pr_info("pgd_kern[%d]=%lx\n", i, pgdp->pgd);
		pgdp = pgd_base_user + i;
		pr_info("pgd_user[%d]=%lx\n", i, pgdp->pgd);
	}
*/
	return 0; 
}

static void __exit test_exit(void) 
{
} 

module_init(test_init); 
module_exit(test_exit);
MODULE_LICENSE("GPL"); 
