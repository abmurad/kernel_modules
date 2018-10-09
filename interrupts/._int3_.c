/*property of umaraZ Inc written for GLOBALEDGESOFT p LTD */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/unistd.h>
#include <linux/utsname.h>
#include <linux/kallsyms.h>
#include <asm/pgtable.h>

MODULE_LICENSE("GPL");

struct desc_ptr idtr;

gate_desc *_idt_table;

gate_desc *index_gate;

unsigned long error_original ; 

unsigned long old_handler ;

unsigned long old_int3 ;

asmlinkage void my_handler ( struct pt_regs *reg , unsigned long emo ) ;

void some_random_code (void ) 
{
	asm volatile ( 
	
			".align 4 , 0x90 \n"

			"my_int3:"

			"pushl $0 \n"

			"pushl handler_ass( , 1 ) \n"

			"jmp *error_original\n"
	
			::

		);

asmlinkage void my_handler ( struct pt_regs *reg , unsigned long emo ) 
{
	void (*old_int_handler)(struct pt_regs *,long) = (void *) old_handler;

	printk ("good to handle interrupts\n") ;

	(*old_int_handler) (struct pt_regs *reg , unsigned long emo );

}

unsigned long handler_ass=(unsigned long)&my_handler;

unsigned long interrupt_index( int n ) 
{
        asm ("sidt %0" : "=m" (idtr));

        _idt_table = (gate_desc *) idtr.address;

        index_gate = &_idt_table[ n ] ;

        return (index_gate->a & 0xffff) | (index_gate->b & 0xffff0000)  ;


int init_module (void) 
{

	unsigned long new_addr = my_int3 ;

	old_int3 = interrupt_index ( 3 ) ;

	index_gate -> b = (index_gate -> b & 0x0000ffff ) | ( new_addr & 0xffff0000 ) ;

	index_gate -> a = (index_gate -> a & 0xffff0000 ) | ( new_addr & 0x0000ffff ) ;
	
	error_original = kallsyms_lookup_name("error_code");;
	
	old_handler = kallsyms_lookup_name("do_int3");;


	return 0 ;

}

void cleanup_module(void) {

	printk("+ Unloading module\n");
	
	index_gate -> b = (index_gate -> b & 0x0000ffff ) | ( old_int3 & 0xffff0000 ) ;

        index_gate -> a = (index_gate -> a & 0xffff0000 ) | ( old_int3 & 0x0000ffff ) ;

	return ;
}

