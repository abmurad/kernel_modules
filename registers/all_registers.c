#include <linux/module.h>

#include <linux/kernel.h>

int init_module(void)
{
	u32 cr0, cr2, cr3 , cr4 , cr8;
	
	u16 cs , ds , es , gs , ss ;

	asm volatile ("mov %%cr0 , %0 ":"=r"(cr0) );

	asm volatile ("mov %%cr2 , %0 ":"=r"(cr2) );

	asm volatile ("mov %%cr3 , %0 ":"=r"(cr3) );
	
	asm volatile ("mov %%cs , %0 ":"=r"(cs) );

	asm volatile ("mov %%gs , %0 ":"=r"(gs) );

	asm volatile ("mov %%es , %0 ":"=r"(es) );

	asm volatile ("mov %%ss , %0 ":"=r"(ss) );

	asm volatile ("mov %%ds , %0 ":"=r"(ds) );
	
	printk(KERN_INFO "cr0 = 0x%8.8X\n", cr0);

	printk(KERN_INFO "cr2 = 0x%8.8X\n", cr2);

	printk(KERN_INFO "cr3 = 0x%8.8X\n", cr3);
	
	printk(KERN_INFO "cs = 0x%8.8X\n", cs);

	printk(KERN_INFO "gs = 0x%8.8X\n", gs);

	printk(KERN_INFO "es = 0x%8.8X\n", es);

	printk(KERN_INFO "ss = 0x%8.8X\n", ss);

	printk(KERN_INFO "ds = 0x%8.8X\n", ds);


}

void cleanup_module(void)
{

}
