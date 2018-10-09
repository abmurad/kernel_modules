#define __START___EX_TABLE 0xc15e4950
#define __END___EX_TABLE  0xc15e61e0 
#define BAD_GET_USER      0xc1301336

unsigned long start_ex_table = __START___EX_TABLE;
unsigned long end_ex_table = __END___EX_TABLE;
unsigned long bad_get_user = BAD_GET_USER;

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
//#define PDEBUG(fmt, args...) printk(KERN_DEBUG "[fixup] : " fmt, ##args)
#define PDEBUG printk

//MODULE_PARM(start_ex_table, "l");
//MODULE_PARM(end_ex_table, "l");
//MODULE_PARM(bad_get_user, "l");


struct old_ex_entry {
        struct old_ex_entry     *next;
        unsigned long           address;
        unsigned long           insn;
        unsigned long           fixup;
};
  
struct old_ex_entry *ex_old_table;

void hook(void) 
{
        printk(KERN_INFO "Oh Jesus... it works!\n");
} 

void cleanup_module(void)
{
        struct old_ex_entry     *entry = ex_old_table;
        struct old_ex_entry     *tmp;

        if (!entry)
                return;

        while (entry) {
                *(unsigned long *)entry->address = entry->insn;
                *(unsigned long *)((entry->address) + sizeof(unsigned
long)) = entry->fixup;
                tmp = entry->next;
                kfree(entry);
                entry = tmp;
        }

        return;
}


int init_module(void)
{
        unsigned long       insn = start_ex_table;
        unsigned long       fixup;
        struct old_ex_entry *entry, *last_entry;

        ex_old_table = NULL;
        PDEBUG(KERN_INFO "hook at address : %p\n", (void *)hook);

        for(; insn < end_ex_table; insn += 2 * sizeof(unsigned long)) {

                fixup = insn + sizeof(unsigned long);

                if (*(unsigned long *)fixup == BAD_GET_USER) {

                        PDEBUG(KERN_INFO "address : %p insn: %lx fixup : %lx\n",
                                        (void *)insn, *(unsigned long *)insn,
                                        *(unsigned long *)fixup);
        
                        entry = (struct old_ex_entry *)kmalloc(GFP_ATOMIC,
					sizeof(struct old_ex_entry));

			printk("entry %x\n" , entry);
        
                        if (!entry)
                                return -1;

                        entry->next = NULL;
                        entry->address = insn;
                        entry->insn = *(unsigned long *)insn;
                        entry->fixup = *(unsigned long *)fixup;

                        if (ex_old_table) {
                                last_entry = ex_old_table;
        
                        	while(last_entry->next != NULL)
                                	last_entry = last_entry->next;

                                last_entry->next = entry;
                        } else
                                ex_old_table = entry;
                
                        *(unsigned long *)fixup = (unsigned long)hook;
                
                        PDEBUG(KERN_INFO "address : %p insn: %lx fixup : %lx\n",
                                        (void *)insn, *(unsigned long *)insn,
                                        *(unsigned long *)fixup);


                }

        }

        return 0;
}
        
MODULE_LICENSE("GPL");

