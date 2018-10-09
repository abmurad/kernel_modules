#include <linux/init.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/sched/signal.h>
#include <linux/fdtable.h>
#include <linux/pipe_fs_i.h>

static struct task_struct *to_task_struct(char *comm)
{
	struct task_struct *tsk;
	
	for_each_process(tsk) {

		//printk("pgd is %x %x %s\n" , tsk -> mm , tsk -> active_mm , tsk -> comm );

		if (!strcmp(tsk->comm, comm))

			return tsk;
	}

	return 0;
}

static int __init test_init(void)
{
	struct task_struct *task;
	struct task_struct *itask;
	struct task_struct *stask;
	struct mm_struct *mm;
	struct vm_area_struct *vma;

	task = to_task_struct("getchar");
	if (!task)
		return -ECHILD;

	//printk("%x\n" , task -> files -> fdt -> fd[4] -> f_inode -> i_pipe -> user );
//	printk("%x\n" , task -> files -> fdt -> fd[4] -> f_inode -> i_pipe -> bufs -> page -> virtual );
	
//	void *addr = kmap ( task -> files -> fdt -> fd[4] -> f_inode -> i_pipe -> bufs -> page ) ;
	
//	printk("%x\n" , task -> files -> fdt -> fd[4] -> f_inode -> i_pipe -> bufs -> page -> virtual );

//	int index = 0 ;

//	while ( index < 4000 ) 
//		printk("%x\n" , ((char*)addr)[index++] );	

	mm = task->mm;

	//iitask = find_task_by_vpid(1) ;
	//printk("%s %x %x \n" , itask -> comm , itask -> real_parent , itask -> parent );
	//stask = itask -> parent ;
	//printk("pgd is %s\n" , stask -> comm );
//	printk("pgd is %x %x %x\n" , stask -> active_mm -> pgd ,stask -> mm , stask -> active_mm );
//	printk("%s\n" , stask -> comm);
//	printk("%x\n" , stask -> parent);
//	printk("state %x\n" , stask -> state);
//	printk("%x %x\n" , task , find_task_by_vpid(1));
//	send_sig( 2 , task , 2 ) ;
//	task = stask ;

/*	pr_info("lin.addr of 1st allctd mmap_base:\t%lx\n", mm->mmap_base);
	pr_info("task_size:\t%lx\n", mm->task_size);
	pr_info("pgd->pgd:\t%llx\n\n", mm->pgd->pgd);

	pr_info("mm_users:\t%d\n", mm->mm_users.counter);
	pr_info("mm_count:\t%d\n", mm->mm_count.counter);
	pr_info("nr_ptes: \t%d\n", mm->nr_ptes.counter);
	pr_info("map_count:\t%d\n\n", mm->map_count);

	pr_info("total_vm:\t%ld\n", mm->total_vm);
	pr_info("locked_vm:\t%ld\n", mm->locked_vm);
	pr_info("pinned_vm:\t%ld\n", mm->pinned_vm);
	//pr_info("shared_vm:\t%ld\n", mm->shared_vm);
	pr_info("exec_vm: \t%ld\n", mm->exec_vm);
	pr_info("stack_vm:\t%ld\n\n", mm->stack_vm);

	pr_info("start_code: \t0x%08lx\n", mm->start_code);
	pr_info("end_code: \t0x%08lx\n", mm->end_code);
	pr_info("start_data: \t0x%08lx\n", mm->start_data);
	pr_info("end_data: \t0x%08lx\n", mm->end_data);
	pr_info("start_brk: \t0x%08lx\n", mm->start_brk);
	pr_info("brk:       \t0x%08lx\n", mm->brk);
	pr_info("start_stack: \t0x%08lx\n", mm->start_stack);
	pr_info("arg_start: \t0x%08lx\n", mm->arg_start);
	pr_info("arg_end: \t0x%08lx\n", mm->arg_end);
	pr_info("env_start: \t0x%08lx\n", mm->env_start);
	pr_info("env_end: \t0x%08lx\n", mm->env_end);

*/
	vma = mm->mmap;
	for (; vma; vma = vma->vm_next) {
		if (vma->vm_file)
			pr_info("[0x%08lx - 0x%08lx] %s\n", vma->vm_start, vma->vm_end, vma->vm_file->f_path.dentry->d_iname);
		else
			pr_info("[0x%08lx - 0x%08lx]\n", vma->vm_start, vma->vm_end);

			pr_info( "%x\n",vma->vm_flags & VM_GROWSDOWN);
	}
	return 0;
}

static void __exit test_exit(void)
{
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL v2");
