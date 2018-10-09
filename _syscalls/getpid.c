//cat /boot/System.map-3.13.0-32-generic |grep -e "D loops_per_jiffy" -e "sys_call_table" -e "D boot_cpu_data"
//grep sys_call_table /boot/System.map-$(uname -r) |awk '{print $1}'

/*propreitary of umaraZ Inc written for GLOBALEDGESOFT p LTD */
#include	<asm/_umas.h>

#include <linux/module.h>

#include <linux/moduleparam.h>

#include <linux/init.h>

#include <linux/kallsyms.h>

#include <asm/unistd.h>

#include <linux/uaccess.h>

MODULE_LICENSE("GPL v2");

static void **sys_call_table = NULL;

static asmlinkage int (*getpid_old2) (void);

static asmlinkage int getpid_old ( void )
{
        return 1;
}

int just_function(void) 
{
	printk("Iam being called\n");
	
	return 199 ;
}
EXPORT_SYMBOL(just_function);

static int __init set_rick(void)
{

        GPF_DISABLE ;

        sys_call_table = (void **)kallsyms_lookup_name("sys_call_table");

        pr_info("found sys_call_table at %p\n", sys_call_table);

		getpid_old2 = sys_call_table[__NR_getpid] ;
    
	    sys_call_table[__NR_getpid] = getpid_old ;

        GPF_ENABLE ;

        return 0;
}

static void __exit unset_rick(void)
{
        GPF_DISABLE ;

        sys_call_table[__NR_open] = getpid_old2;

        GPF_ENABLE ;
}

module_init(set_rick);

module_exit(unset_rick);
