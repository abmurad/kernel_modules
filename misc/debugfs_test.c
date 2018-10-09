/*
 * some code copy from drivers/clk/clk.c.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/fs.h>

struct dentry *rootdir;

static int foo_show(struct seq_file *s, void *data)
{
	seq_puts(s, "hello\n");
	return 0;
}

static int foo_open(struct inode *inode, struct file *file)
{
	return single_open(file, foo_show, inode->i_private);
}

static const struct file_operations foo_fops = {
	.open		= foo_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init test_debug_init(void)
{
	struct dentry *foo;

	rootdir = debugfs_create_dir("test_debugfs", NULL);
	if (!rootdir) {
		pr_err("failed to create debugfs root directory.\n");
		return -ENOMEM;
	}

	foo = debugfs_create_file("foo", S_IRUGO, rootdir, NULL, &foo_fops);
	if (!foo) {
		pr_err("Failed to create debugfs at foo\n");
		return -ENOMEM;
	}

	return 0;
}

static void __exit test_debug_exit(void)
{
	debugfs_remove_recursive(rootdir);
}

module_init(test_debug_init);
module_exit(test_debug_exit);

MODULE_LICENSE("GPL");
