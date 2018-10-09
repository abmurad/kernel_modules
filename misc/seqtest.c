#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/rwsem.h>

DECLARE_RWSEM(crypto_alg_sem);

static int n = 0;

static int show_test(struct seq_file *m, void *v)
{
	seq_printf(m, "hello, world!\n");
	return 0;
}

static void *t_start(struct seq_file *m, loff_t *pos)
{
	down_read(&crypto_alg_sem);
	if (n < 4)
		return m;
	else
		return NULL;
}

static void *t_next(struct seq_file *m, void *v, loff_t *pos)
{
	n++;
	return t_start(m, pos);
}

static void t_stop(struct seq_file *m, void *v)
{
	up_read(&crypto_alg_sem);
}

const struct seq_operations test_op = {
	.start  = t_start,
	.next   = t_next,
	.stop   = t_stop,
	.show   = show_test,
};

static int test_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &test_op);
}

const struct file_operations fop = {
	.open       = test_open,
	.read       = seq_read,
	.llseek     = seq_lseek,
	.release    = seq_release,
};

static int __init test_init(void)
{
	struct proc_dir_entry *file;

	file = proc_create("file", 0, NULL, &fop);
	if (!file) {
		goto err_file_entry;
	}

	return 0;

err_file_entry:
	remove_proc_entry("file", NULL);
	return -1;
}

static void __exit test_exit(void)
{
	remove_proc_entry("file", NULL);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
