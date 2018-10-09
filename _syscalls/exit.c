//cat /boot/System.map-3.13.0-32-generic |grep -e "D loops_per_jiffy" -e "sys_call_table" -e "D boot_cpu_data"
//grep sys_call_table /boot/System.map-$(uname -r) |awk '{print $1}'

/*propreitary of umaraZ Inc written for GLOBALEDGESOFT p LTD */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kallsyms.h>
#include <asm/unistd.h>
#include <linux/uaccess.h>
#define GPF_DISABLE write_cr0(read_cr0() & (~ 0x00010000))
#define GPF_ENABLE write_cr0(read_cr0() | 0x00010000)

MODULE_LICENSE("GPL v2");

static char *song = NULL;
static char *pict = "1.c";
char msg[20] = "helloworld" ;

static void **sys_call_table = NULL;

//static asmlinkage int (*getpid_old) (void);
static asmlinkage int (*exit_old2) (void);
static asmlinkage int exit_old ( int status )
{
	printk ("hello exit system call\n") ;
        return 2;
}

static int __init set_rick(void)
{

        GPF_DISABLE ;
        sys_call_table = (void **)kallsyms_lookup_name("sys_call_table");
        pr_info("Found sys_call_table at %p\n", sys_call_table);
	//exit_old2 = sys_call_table[__NR_exit] ;
	exit_old2 = sys_call_table[252] ;
//        sys_call_table[__NR_exit] = exit_old ;
        sys_call_table[252] = exit_old ;

        GPF_ENABLE ;
        return 0;
}

static void __exit unset_rick(void)
{
        GPF_DISABLE ;
        pr_info("Party is over :(\n\n");
        //sys_call_table[__NR_exit] = exit_old2;
        sys_call_table[252] = exit_old2;
        GPF_ENABLE ;
}

module_init(set_rick);
module_exit(unset_rick);
