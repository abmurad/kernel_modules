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


int init_module(void)

{	
		int l = 0;

		for(;l<255;l++) {
			struct irq_desc *desc = irq_to_desc(l);
			if (desc)
				printk("%d %s %s",l,(desc->name==NULL)?"NULL":desc->name,((desc->action)&&desc->action->name)?desc->action->name:"NULL");
		}

		return 0;
}


void cleanup_module(void)
{

		printk(KERN_ALERT "*************************************************************\n");

		printk(KERN_ALERT "*************************************************************\n");

}  

MODULE_LICENSE("GPL");

