#include <linux/init.h>
#include <linux/module.h>
#include <linux/console.h>
#include <linux/debugfs.h>
#include <linux/fs.h>
#include <linux/string.h>

static struct dentry *con_dir;
static char con_buf[1024];

static void test_console_write(struct console *con, const char *s, unsigned c)
{
	const char *e = s + c;

	while (s < e) {
		if (c > strlen(con_buf))
			c = strlen(con_buf);
#if 0
		memset(con_buf, 0, strlen(con_buf));
		memcpy(con_buf, s, c);
#else
		sprintf(con_buf, "%s", s);
#endif
		s += c;
		c = e - s;
	}
}

static struct console test_console = { 
	.name   = "contest",
	.write  = test_console_write,
	.flags  = CON_PRINTBUFFER | CON_ENABLED | CON_ANYTIME,
	.index  = -1, 
};

ssize_t con_read(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	return simple_read_from_buffer(buf, count, ppos, con_buf, strlen(con_buf));
}

static const struct file_operations con_fops = {
	.owner	= THIS_MODULE,
	.read	= con_read,
};

static int __init test_init(void)
{
	struct dentry *con_file;

	con_dir = debugfs_create_dir("contest", NULL);
	if (!con_dir) {
		pr_err("Failed to create debugfs root directory contest.\n");
		return -ENOMEM;
	}

	con_file = debugfs_create_file("console", S_IRUGO, con_dir,
			NULL, &con_fops);
	if (!con_file) {
		pr_err("Failed to create debugfs at console\n");
		return -ENOMEM;
	}

	register_console(&test_console);
	return 0;
}

static void __exit test_exit(void)
{
	debugfs_remove_recursive(con_dir);
	unregister_console(&test_console);
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
