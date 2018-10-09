#include <linux/init.h>
/** System Includes **/
#include <linux/init.h>
#include <linux/genhd.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>
#include<linux/fdtable.h>

#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/posix_types.h>
#include <linux/compiler.h>
#include <linux/spinlock.h>
#include <linux/rcupdate.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/fs.h>

#include <linux/netdevice.h>
#include <linux/atomic.h>
#include <linux/slab.h>

#include </usr/src/linux-4.11/fs/ext4/ext4.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/path.h>
#include <linux/list.h>
#include <linux/spinlock.h>

static int __init subdirstest_init(void)
{
	struct dentry *parent = current->fs->pwd.dentry;
	struct inode *parent99 = current->fs->pwd.dentry->d_inode;
	printk("d_name: %s\n", parent->d_name.name);
	struct ext4_inode_info *inode = EXT4_I(parent99);
	if (inode)
		//printk("disk size %x\n",inode);
		printk("disk size %x\n",inode->i_data[2]);
	//printk("disk size %u\n",inode->i_disksize);
	else
		printk("inode is NULL\n");


	struct fdtable *fdt_u = current -> files -> fdt ;

	struct file *file_u = * ( fdt_u -> fd ) ;

	struct inode *inode_u = file_u -> f_inode ;

	inode = EXT4_I(inode_u);

	if (inode)
		printk("disk size %x\n",inode->i_data[0]);
	//printk("disk size %u\n",inode->i_disksize);
	else
		printk("inode is NULL\n");



	return 0;
}

static void __exit subdirstest_exit(void)
{
}

module_init(subdirstest_init);
module_exit(subdirstest_exit);
