#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <asm/cacheflush.h>
#include <linux/syscalls.h>
#include <linux/delay.h>

#define __NR_unused 223

static int orig_cr0;
static unsigned long *syscall_table;
static int (*anything_saved)(void);

static unsigned long **find_syscall_table(void)
{
	unsigned long ptr;
	unsigned long *p;

	for (ptr = (unsigned long)sys_close;
	     ptr < (unsigned long)&loops_per_jiffy;
	     ptr += sizeof(void *)) {
		p = (unsigned long *)ptr;

		if (p[__NR_close] == (unsigned long)sys_close) {
			pr_debug("Found the syscall_table!!!\n");
			return (unsigned long **)p;
		}
	}

	return NULL;
}

static unsigned int clear_and_return_cr0(void)
{
	unsigned int cr0 = 0;
	unsigned int ret;

	asm volatile ("movl %%cr0, %%eax" : "=a"(cr0));
	ret = cr0;

	/*clear the 20th bit of CR0,*/
	cr0 &= 0xfffeffff;
	asm volatile ("movl %%eax, %%cr0" : : "a"(cr0));
	return ret;
}

static void setback_cr0(unsigned int val)
{
	asm volatile ("movl %%eax, %%cr0" : : "a"(val));
}

static asmlinkage long sys_mycall(void)
{
	pr_debug("I am mycall.current->pid = %d, current->comm = %s\n",
			current->pid, current->comm);
	return current->pid;
}

static int __init init_addsyscall(void)
{
	syscall_table = (unsigned long *)find_syscall_table();
	anything_saved = (int(*)(void))(syscall_table[__NR_unused]);

	orig_cr0 = clear_and_return_cr0();
	syscall_table[__NR_unused] = (unsigned long)&sys_mycall;
	setback_cr0(orig_cr0);

	return 0;
}

static void __exit exit_addsyscall(void)
{
	orig_cr0 = clear_and_return_cr0();
	syscall_table[__NR_unused] = (unsigned long)anything_saved;
	setback_cr0(orig_cr0);
}

module_init(init_addsyscall);
module_exit(exit_addsyscall);

MODULE_LICENSE("GPL");
