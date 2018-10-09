#define DISABLE write_cr0(read_cr0() & (~ 0x00010000))
#define ENABLE write_cr0(read_cr0() | 0x00010000)

#include <linux/module.h>
#include <linux/tty.h>
#include <linux/sched.h>
#include <linux/kallsyms.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <linux/uaccess.h>
#include <asm/timex.h>

int int_num = -1 ;

int flag = 1 ;

char *exp_name = NULL ;

module_param(int_num , int , 0644);

module_param( exp_name , charp , 0644);

asmlinkage void my_handler(struct pt_regs * regs,long err_code);

unsigned long ptr_idt_table;
unsigned long ptr_gdt_table;
unsigned long old_interrupt;
unsigned long old_handler ;
unsigned long old_error_code ;;
unsigned long ptr_handler=(unsigned long)&my_handler;
extern asmlinkage void my_interrupt(void);

struct descriptor_idt
{
	unsigned short offset_low,seg_selector;
	unsigned char reserved,flag;
	unsigned short offset_high;
};

void int_3_kad(void)
{
	DISABLE ;
	asm volatile (
			".align 4,0x90                  \n"
			"my_interrupt:                       \n"
			"pushl $0                       \n"
			"pushl ptr_handler(,1)          \n"
			"jmp *old_error_code             "
			::
		     );
	ENABLE;
}

asmlinkage void my_handler(struct pt_regs * regs,long err_code)
{

	DISABLE ;

	void (*old_int_handler)(struct pt_regs *,long) = (void *) old_handler;

	printk("\n\n********************finally interrupt is handled*******************************\n\n\n");

	(*old_int_handler)(regs,err_code);

	ENABLE ;

	return;

}

struct desc_ptr_local {
        unsigned short size;
        unsigned long address;
} __attribute__((packed)) ;


unsigned long get_addr_idt (void)
{
	unsigned char idtr[6];
	
	unsigned long idt;

	__asm__ volatile ("sidt %0": "=m" (idtr));

	idt = *((unsigned long *) &idtr[2]);

	struct desc_ptr gdt , idt_o , ldt  ;

	unsigned long ass_ldt = 0 ;

        asm volatile("sgdt %0":"=m" (gdt));
        
	asm volatile("sidt %0":"=m" (idt_o));
	
	asm volatile("sldt %0":"=m" (ldt));

/*	printk ("ldt address is %x\n" , ldt . address  ) ;
	
	printk ("ass ldt address is %x\n" , *(int*)(((char*) gdt . address ) + (15 * 8) )) ;
	
	printk ("gdt address is %x\n" , gdt . address  ) ;
	
	printk ("gdt size is %x\n" , gdt . size ) ;
	
	printk ("idt address is %x\n" , idt_o . address  ) ;
	
	printk ("idt address manually is %x\n" , (unsigned long )idt  ) ;
*/
	return(idt);
}

void * get_int_from_idt (int n)
{
	struct descriptor_idt *idte = &((struct descriptor_idt *) ptr_idt_table) [n];

//	printk ("seg_selector %x %x \n" ,idte -> seg_selector , ((void *) ((idte->offset_high << 16 ) + idte->offset_low)) ) ;

	return ((void *) ((idte->offset_high << 16 ) + idte->offset_low));
}

void hook_interrupt(int n,void *new_interrupt,unsigned long *old_interrupt)
{
	unsigned long new_addr ;

	DISABLE ;

	new_addr =(unsigned long)new_interrupt;

	struct descriptor_idt *idt=(struct descriptor_idt *)ptr_idt_table;

	if(old_interrupt) {

		*old_interrupt=(unsigned long)get_int_from_idt( int_num );
	
//		 printk ( "last trail reasulted in %x\n" ,*(int*)((char*)old_interrupt + 0x60) ) ;

	}

	idt[n].offset_high = (unsigned short) (new_addr >> 16);

	idt[n].offset_low  = (unsigned short) (new_addr & 0x0000FFFF);

	ENABLE ;
	return;
}

int init_module(void)
{

	if ( int_num == -1 || exp_name == NULL ) {

		printk(KERN_EMERG"need module parameters\n");

		flag = 0 ;

		return 0 ;

	}

	unsigned long ini , end ;

	//rdtscl(ini) ; rdtscl(end) ;

/*	printk ("time laps through registers %li\n" , get_cycles() );

	printk ("%u\n" , HZ ) ;

	printk ("time after %d \n" , time_after ( jiffies + HZ , jiffies));
	
	printk ("time after reverse %d \n" , time_before ( jiffies  , jiffies + HZ ));

	ndelay(1);

	mdelay(1);

	udelay(1);

	msleep_interruptible(1);

	ssleep(1);

	unsigned long int stamp = 0 ;

	stamp = jiffies + 10 * HZ ;

	//msleep(10);
	
	//while ( !time_after ( jiffies , stamp ) ) asm volatile ( "rep ; nop ") ; // or schedule() ;

	printk ("milli seconds are %d\n" , (- (long)stamp + (long) (jiffies) )*  4 );
*/
	ptr_idt_table=get_addr_idt(); //get idt address

	old_handler = kallsyms_lookup_name(exp_name) ;
	
	old_error_code=kallsyms_lookup_name("error_code");;

	hook_interrupt( int_num , &my_interrupt , &old_interrupt );

	return 0;
}

void cleanup_module()

{
	if ( flag ) 

	hook_interrupt(int_num,(char *)old_interrupt, NULL );

	//printk ("module unloaded %d\n" , sys_getpid()) ;	

	ENABLE ;
}

MODULE_AUTHOR("saraboju umaraju charY");

MODULE_DESCRIPTION ("learning to define device behaviour");

MODULE_LICENSE("GPL v2");
