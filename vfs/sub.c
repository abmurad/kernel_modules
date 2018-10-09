#include <linux/init.h>
#include </usr/src/linux-4.13.2+/fs/ext4/ext4.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/path.h>
#include <linux/list.h>
#include <linux/spinlock.h>

void parse_item(struct dentry*,int );
//extern int ext4_get_inode_loc(struct inode *, struct ext4_iloc *);



struct dentry *get_dent(char *str)
{
;
}

void parse_dir(struct dentry *parent,int val)
{

	//printk("%*s DIRECTORY : %s\n",val,"", parent->d_name.name);

	struct dentry *child;
	list_for_each_entry(child, &parent->d_subdirs, d_child){
	if (!strcmp("saraboju",child->d_name.name)){
	struct ext4_inode_info	*inode = EXT4_I(child->d_inode);
		printk("found home %x %d %d\n",inode,inode->i_block_group,inode->i_dir_start_lookup);
		 //struct ext4_iloc iloc;
		 //ext4_get_inode_loc(child->d_inode, &iloc);
		//printk(" %u %u %s\n",iloc.offset,iloc.block_group,iloc.bh->b_data);
	}
		parse_item(child,val+1);

	}
}

void parse_file(struct dentry *dent,int val)
{
	printk("%*s FILE : %s ",val,"", dent->d_name.name);
/*
	struct ext4_inode_info	*inode = EXT4_I(dent->d_inode);
	if (inode)
		printk("\t\tdisk size %u\n",inode->i_disksize);
	else
		printk("\t\tinode is NULL\n");
*/
}

void parse_item(struct dentry *child,int val)
{
	spin_lock(&child->d_lock);
	

	if ( (0x00200000 & child->d_flags) && (0x00400000 & child->d_flags) == 0 ) {
		parse_dir(child,val+1);
	}
	else if ( 0x00400000 & child->d_flags ) {
		parse_file(child,val);
	}
	spin_unlock(&child->d_lock);

}


static int __init subdirstest_init(void)
{
	struct dentry *parent = current->fs->root.dentry;
	struct inode *parent99 = current->fs->pwd.dentry->d_inode;
	struct dentry *child;
	struct ext4_inode_info *inode = NULL;

	spin_lock(&parent->d_lock);

	list_for_each_entry(child, &parent->d_subdirs, d_child) {

		parse_item(child,0);
	}
	spin_unlock(&parent->d_lock);
	return 0;
}

static void __exit subdirstest_exit(void)
{
}

module_init(subdirstest_init);
module_exit(subdirstest_exit);
