/*propreitary of umaraZ Inc written for GLOBALEDGESOFT p LTD */



#include <asm/_umas.h>

#include <linux/kernel.h>

#include <linux/irq.h>

#include <linux/input.h>

#include <asm/irq.h>

#include <linux/delay.h>

#include <linux/module.h>

#include <linux/interrupt.h>

#include <asm/io.h>

static int setkeycode(unsigned int scancode, unsigned int keycode) ;

void print_key ( unsigned char ) ;

int my_irq_num = 1 ;

unsigned long irq_state = 0 ;

irq_handler_t irq_thread (int irq, void *dev_id, struct pt_regs *regs) {

	printk("in thread function\n");
	
	return IRQ_HANDLED ;

}

irq_handler_t irq_handler (int irq, void *dev_id, struct pt_regs *regs) {

	static unsigned char scancode;

	scancode = inb (0x60);

//		printk("scancode %x\n" , scancode) ;

//	print_key(scancode) ;
	
	GPF_DISABLE ;
	
//	printk ( "%d set keycode returned \n" , setkeycode(scancode, scancode+1 ) );
		
//	outb ( scancode  ,  0x64  ) ;

	GPF_ENABLE ;

	return (irq_handler_t) IRQ_WAKE_THREAD;

	//	return (irq_handler_t) IRQ_ONE ;

	//	return (irq_handler_t) IRQ_WAKE_THREAD;

}

/* Initialize the module and Register the IRQ handler */

static int __init keybrd_int_register(void)
{

	int result;

	int short_base = 0x378 ;

	int count = 0;

	/*do {

	unsigned long int bitmask_irq  ;

	bitmask_irq = probe_irq_on();

	outb_p (0x10 , short_base+2);

	outb_p (0x00 , short_base );
	
	outb_p (0xff , short_base );
	
	outb_p (0x00 , short_base+2 );
	
	udelay(5);

	//printk("the unassigned interrupt num mask is %lu\n" , bitmask_irq);

	my_irq_num = probe_irq_off( bitmask_irq );

	if ( my_irq_num == 0 ) {

		printk("no irq reported\n");
	
		my_irq_num  = -1 ;

	}*/

	//}while ( my_irq_num < 0 && count ++ < 5 ) ;

	//printk("probe failed %i times \n" , count);
		
	/* Request IRQ 1, the keyboard IRQ */    

//	printk ( "can_request_irq returned %d\n" , can_request_irq(2, 0));

//	result = request_irq (1, (irq_handler_t) irq_handler, IRQF_SHARED /*IRQF_TIMER*/ /*IRQF_PERCPU*/ , "keyboard_stats_irq", (void *)(irq_handler));
	
	result = request_threaded_irq (my_irq_num, (irq_handler_t) irq_handler,  (irq_handler_t)irq_thread ,IRQF_SHARED /*IRQF_TIMER*/ /*IRQF_PERCPU*/ , "custom_irq_GES", (void *)(irq_handler));
	
	//result = request_irq (my_irq_num, (irq_handler_t) irq_handler, IRQF_SHARED /*IRQF_TIMER*/ /*IRQF_PERCPU*/ , "custom_irq_GES", (void *)(irq_handler));

//	asm volatile( "cli" ) ;

//	disable_irq(1);

//	local_irq_save(irq_state) ;
	
//	local_irq_disable();

//	disable_irq(1) ;

	if (result)

		printk(KERN_INFO "can't get shared interrupt for keyboard\n");

	return result;
}

/* Remove the interrupt handler */

static void __exit keybrd_int_unregister(void) {

	printk ("**********************************\n") ;

//	enable_irq(1);

//	local_irq_restore( irq_state );

//	local_irq_enable();

//	enable_irq(1);

//	asm volatile( "sti" ) ;

	free_irq(my_irq_num, (void *)(irq_handler)); /* can't pass NULL, this is a shared interrupt handler! */

//	free_irq(1, NULL); 

}

MODULE_LICENSE ("GPL v2");
module_init(keybrd_int_register);
module_exit(keybrd_int_unregister);
