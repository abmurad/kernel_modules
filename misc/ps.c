#include	<linux/module.h>

#include	<linux/init.h>

#include	<linux/fs.h>

#include	<linux/sched.h>

int init_module( void ) 
{

    struct task_struct *task = get_current() ;;

    task = (current_thread_info()->task) ;

    int cr3 = 1 ;

    for(task = &init_task; cr3 || task != &init_task ; task = next_task(task)) {

        cr3 = 0;

        printk(" %10d %10d %3d\t%s\n" , task -> pid , task -> parent -> pid , task -> state ,task -> comm ) ;

    }

    return 0 ;

}

void cleanup_module( void ) 
{
	return ;	
}


