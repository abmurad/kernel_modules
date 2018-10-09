#include <linux/syscalls.h>
#include <linux/errno.h>

#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/fs.h>

int write_console (char *str)
{
	struct tty_struct *my_tty;

	if((my_tty=current->signal -> tty) != NULL)

	{
		(my_tty->driver -> ops -> write)(my_tty , str , strlen(str))  ;

		return 0;
	}

	else return -1;

}

EXPORT_SYMBOL( write_console );

int init_module(void)

{
	return 0 ;

}


void cleanup_module(void)
{
}  

MODULE_LICENSE("GPL");

