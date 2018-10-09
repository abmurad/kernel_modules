#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/types.h> /* size_t */
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/switch_to.h>
#include <asm/uaccess.h> /* copy_from/to_user */
#include <linux/fs.h>       // for basic filesystem
#include <linux/mm.h>       // for basic filesystem
#include <linux/proc_fs.h>  // for the proc filesystem
#include <linux/seq_file.h> // for sequence files
#include <linux/mmzone.h>


#include <linux/types.h> /* size_t */
#include <linux/slab.h> /* size_t */
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/switch_to.h>
#include <asm/uaccess.h> /* copy_from/to_user */
#include <linux/fs.h>       // for basic filesystem
#include <linux/mm.h>       // for basic filesystem
#include <linux/proc_fs.h>  // for the proc filesystem
#include <linux/seq_file.h> // for sequence files
#include <linux/mmzone.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>

static void trace(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);

static struct jprobe jp = {
	.entry = JPROBE_ENTRY(trace),
	.kp = {
		.symbol_name = NULL,
	}
};

static void trace(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5)
{
	printk("]=------------------------\n");
	printk("Function  : %s\n\n", jp.kp.symbol_name);
	printk("Arg0 : %08x    Arg1 : %08x    Arg2 : %08x\n",   (unsigned int)arg0, (unsigned int)arg1, (unsigned int)arg2);
	printk("Arg3 : %08x    Arg4 : %08x    Arg5 : %08x\n\n", (unsigned int)arg3, (unsigned int)arg4, (unsigned int)arg5);
	dump_stack();
	printk("]= EOF -------------------\n");
	jprobe_return();
}

static ssize_t handler_proc_write(struct file *file, const char __user *buffer, unsigned long count, void *data)
{
	int ret;

	if (jp.kp.symbol_name)
		kfree(jp.kp.symbol_name);

	jp.kp.symbol_name = kzalloc(count +1, GFP_KERNEL);
	if (!jp.kp.symbol_name)
		return -ENOMEM;

	memcpy((void*)jp.kp.symbol_name, (void *)buffer, count);
	if (!memcmp(jp.kp.symbol_name, "none", 4)){
		kfree(jp.kp.symbol_name);
		jp.kp.symbol_name = NULL;
		unregister_jprobe(&jp);
		printk("trace: Tracing stoped\n");
		return count;
	}
	else if ((ret = register_jprobe(&jp)) < 0) {
		printk("trace: register_jprobe failed, returned %d\n", ret);
		kfree(jp.kp.symbol_name);
		jp.kp.symbol_name = NULL;
		return -ENOSYS;
	}
	printk("trace: %s traced\n", jp.kp.symbol_name);
	return count;
}

static ssize_t handler_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int ret;

	if (!jp.kp.symbol_name){
		sprintf(page, "Function traced : none\n");
		ret = 23;
	}
	else {
		sprintf(page, "Function traceed : %s\n", jp.kp.symbol_name);
		ret = strlen(jp.kp.symbol_name) + 20;
	}
	return ret;
}
struct file_operations f_ops = {
	.owner = THIS_MODULE,
	.read = handler_proc_read,
	.write = handler_proc_read,
};

static int __init mod_init(void)
{
	struct proc_dir_entry *proc_entry;

	proc_entry = proc_create("uma_map", 0, NULL,&f_ops);
	if(!proc_entry){
		printk(KERN_ALERT "Error: Could not initialize /proc/uma_map");
		return -ENOMEM;
	}


	return 0;
}

static void __exit mod_exit(void)
{
	unregister_jprobe(&jp);
	remove_proc_entry("trace", NULL);
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");

