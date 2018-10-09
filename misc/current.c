#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs_struct.h>
#include <linux/path.h>
#include <linux/dcache.h>
#include <linux/fdtable.h>
#include <linux/fs.h>
#include <linux/path.h>

static int __init current_test_init(void)
{
	struct fs_struct *fs = current->fs;
	struct path *pwd = &(fs->pwd);
	struct dentry *dentry = pwd->dentry;
	struct qstr *d_name = &(dentry->d_name);
	const unsigned char *name = d_name->name;

	struct files_struct *files = current->files;
	struct file *fd_array = files->fd_array[2];
	struct path f_path = fd_array->f_path;

	pr_info("comm: %s\n", current->comm);
	pr_info("pid: %d\n", current->pid);
	pr_info("pwd name: %s\n", name);
	pr_info("pwd name: %s\n", current->fs->pwd.dentry->d_name.name);
	pr_info("name: %s\n", f_path.dentry->d_name.name);
	return 0;
}

static void __exit current_test_exit(void)
{
}

module_init(current_test_init);
module_exit(current_test_exit);
