#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include<linux/sched.h>
#include <linux/rcupdate.h>
#include <linux/fdtable.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/dcache.h>


MODULE_LICENSE("Dual BSD/GPL");

static int current_init(void)
{

 char *cwd;
        struct path pwd, root; 
 pwd = current->fs->pwd;
 path_get(&pwd);
 root=  current->fs->root;
 path_get(&root);
 char *buf = (char *)kmalloc(GFP_KERNEL,100*sizeof(char));
 cwd = d_path(&pwd,buf,100*sizeof(char));
 printk(KERN_ALERT "Hello,the current working directory is \n %s",cwd);

 return 0;
}

static void current_exit(void)
{

 printk(KERN_ALERT "Goodbye cruel world");
}

module_init(current_init);
module_exit(current_exit);

