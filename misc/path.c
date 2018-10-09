#include <linux/init.h>
#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/gfp.h>
#include <linux/kallsyms.h>
#include <linux/pipe_fs_i.h>
#include <linux/fdtable.h>
#include <linux/fs_struct.h>
#include <linux/path.h>
#include <linux/spinlock.h>
//#include <linux/sched/signal.h>
struct task_struct* to_task_struct(char * comm)

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
		struct task_struct *inst  = NULL ;

		inst = to_task_struct("someapp");

		if ( !inst ) return -ENOMEM ;

		struct dentry *parent = current->fs->pwd.dentry;

		struct dentry *child;

		struct path *root = &inst -> fs -> pwd ;	

		struct dentry *dent = root -> dentry ;

		struct dentry *dent2 = NULL ;
		
		struct dentry *dent3 = dent ;

		int x = 5 ;

		spin_lock( &dent3 -> d_lock ) ;

		do {
//				spin_unlock( &dent -> d_lock ) ;

//				if ( strstr( (char*)dent -> d_iname , "umaraju" ) != NULL )  
				spin_trylock( &dent -> d_lock ) ;

				printk("%s\n" , (char*)dent -> d_iname );

				spin_unlock( &dent -> d_lock ) ;
				dent = ( (char*)dent -> d_subdirs . next ) - offsetof ( struct dentry , d_subdirs ) ;

		}while ( dent != dent3  ) ;

		spin_unlock( &dent3 -> d_lock ) ;

		return 0; 
}

static void __exit test_exit(void) 
{
} 

module_init(test_init); 
module_exit(test_exit);
MODULE_LICENSE("GPL"); 
