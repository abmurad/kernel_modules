
//cat /boot/System.map-3.13.0-32-generic |grep -e "D loops_per_jiffy" -e "sys_call_table" -e "D boot_cpu_data"
//grep sys_call_table /boot/System.map-$(uname -r) |awk '{print $1}'
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

static asmlinkage long (*old_open) (const char __user *filename, int flags, umode_t mode);
static asmlinkage long (*old_write) (int fd , const void __user *buf, size_t count);
static unsigned long **find_sys_call_table(void) ;
static asmlinkage long rick_open(const char __user *filename, int flags, umode_t mode)
{
	size_t len = strlen(filename);
	const char *ext = filename + len - 2;
	if (strncmp(ext, ".c", 2) == 0 && song == NULL)
	  {
	  //copy_to_user((void *)filename, song, len);
	//  }*/
	//if (strncmp(ext, ".c", 2) == 0 && pict != NULL)
	//{
		/*mm_segment_t old_fs;
		long fd;

		old_fs = get_fs();

		set_fs(KERNEL_DS);

		set_fs(old_fs);*/
		
		//copy_to_user((void *)filename, "hello world", 11);
		
		copy_to_user((void *)filename, "1.c", 3);
	
//		copy_to_user ( msg , "umaraju" , 11 ) ;
	}
	pr_info("Let's play!\n");
	printk ("%d\n" , ( old_write ( 1 , filename , 11 ))) ;
	copy_to_user((void *)filename, pict, len);
	return old_open(filename, flags, mode);
}

static int __init set_rick(void)
{
	unsigned int cr0 = 0 ;

	if (song == NULL && pict == NULL)
	{
		pr_info("Rickroll module not loaded. You need to provide a song and/or a picture as a parameter\n");
		return -1;
	}

	asm volatile ("mov %%cr0 , %0 ":"=r"(cr0) );

	printk ("cr0 contents are %0x\n" , cr0 ) ;

	GPF_DISABLE ;
	sys_call_table = (void **)kallsyms_lookup_name("sys_call_table");
	pr_info("Found sys_call_table at %p\n", sys_call_table);
	old_open = sys_call_table[__NR_open];
	old_write = sys_call_table[__NR_write];
	sys_call_table[__NR_open] = rick_open;
	pr_info("Old open: %p; Rick open: %p\n", old_open, rick_open);
	GPF_ENABLE ;
	return 0;
}

static void __exit unset_rick(void)
{
	GPF_DISABLE ;
	pr_info("Party is over :(\n");
	sys_call_table[__NR_open] = old_open;
	GPF_ENABLE ;
}

module_init(set_rick);
module_exit(unset_rick);
