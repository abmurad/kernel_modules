#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/path.h>
#include <linux/list.h>
#include <linux/spinlock.h>

static int __init subdirstest_init(void)
{
    struct dentry *parent = current->fs->root.dentry;
    struct dentry *child;
    
    spin_lock(&parent->d_lock);
    list_for_each_entry(child, &parent->d_subdirs, d_subdirs) {
        spin_lock(&child->d_lock);
        printk("d_name: %s\n", child->d_name.name);
        spin_unlock(&child->d_lock);
    }
    spin_unlock(&parent->d_lock);

	return 0;
}

static void __exit subdirstest_exit(void)
{
}

module_init(subdirstest_init);
module_exit(subdirstest_exit);
