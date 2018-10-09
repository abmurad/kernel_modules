#include <linux/init.h>
#include <linux/module.h>
#include <linux/namei.h>
#include <linux/mount.h>
#include <linux/fs.h>
#include <linux/mm_types.h>

static int __init path_test_init(void)
{
	struct path p;
	struct dentry *d;
	struct inode *ino;
	struct address_space *as;
	struct radix_tree_root *rtr;
	struct page *pg;

	int err = kern_path("/home/saraboju/Downloads/umas_forte/.eGo/zourneY/kernel_hacKs/misc/kern_path.c", LOOKUP_FOLLOW, &p);
	if (err) {
		printk(KERN_ALERT "kern_path failed\n");
		return err;
	}

	printk(KERN_ALERT "mnt_root: %s\n", p.mnt->mnt_root->d_iname);

	d = p.dentry;
	printk(KERN_ALERT "name: %s\n", d->d_name.name);
	printk(KERN_ALERT "d_iname: %s\n", d->d_iname);

	ino = d->d_inode;
	printk(KERN_ALERT "i_ino: %ld\n", ino->i_ino);

	as = ino->i_mapping;
	printk(KERN_ALERT "host: %ld\n", as->host->i_ino);
	printk(KERN_ALERT "nrpages: %ld\n", as->nrpages);

	rtr = &as->page_tree;
//	printk(KERN_ALERT "page_tree height: %d\n", rtr->height);

	pg = (struct page *)radix_tree_lookup(rtr, 10);
	printk(KERN_ALERT "flags: %ld\n", pg->flags);
	printk(KERN_ALERT "index: %ld\n", pg->index);
	printk(KERN_ALERT "_mapcount: %d\n", pg->_mapcount.counter);

	return 0;
}

static void __exit path_test_exit(void)
{
}

module_init(path_test_init);
module_exit(path_test_exit);
