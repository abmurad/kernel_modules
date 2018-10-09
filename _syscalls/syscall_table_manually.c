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

#define MAX_LEN 256
#define PROC_V "/proc/version"


char *ver = NULL ;

	char* kern_ver = NULL ;

int init_module(void)

{


	struct file *f;
	mm_segment_t oldfs;	
	char buf[MAX_LEN] ;
	int i = 0 ;
	int count = 0 ;

	oldfs = get_fs();
	set_fs (KERNEL_DS);
	

	printk("----------------------------------------------------------------------");

	f = filp_open(PROC_V, O_RDONLY, 0);

	if ( IS_ERR(f) || ( f == NULL )) {

		return -1 ;

	}

	memset(buf, 0, MAX_LEN);

	vfs_read(f, buf, MAX_LEN, &f->f_pos);


	while ( i < 256 ) {

		if ( buf[i] == ' ' ) {

			count++ ;

			buf[i] = '\0' ;

			if ( count == 2 ) { 

				ver = buf + i + 1 ;
			}

			if ( count == 3 ) 

				break ;
		}


		i++ ;

	}

	printk(KERN_ALERT "Kernel version found: %s\n", ver);

	filp_close(f, 0);   

	set_fs(oldfs);

	printk("----------------------------------------------------------------------");

	return 0;
}


void cleanup_module(void)
{
	#define BOOT_PATH "/boot/System.map-"

	char buf[MAX_LEN];

	int i = 0;
	char *filename;
	char *p;
	struct file *f = NULL;

	long long syscall_table = 0 ;
				
	char *sys_string;

	mm_segment_t oldfs;

	oldfs = get_fs();
	set_fs (KERNEL_DS);

	kern_ver = ver ;

//	kern_ver = kmalloc(11, GFP_KERNEL);

	printk("%s\n" , kern_ver);
	
//	memset(kern_ver, 0, 11);

//	memcpy ( kern_ver , ver , 11 ) ;

	printk(KERN_ALERT "*************************************************************\n");

	filename = kmalloc(strlen(kern_ver)+strlen(BOOT_PATH)+1, GFP_KERNEL);

	if ( filename == NULL ) {

		return ;

	}

	memset(filename, 0, strlen(BOOT_PATH)+strlen(kern_ver)+1);

	strncpy(filename, BOOT_PATH, strlen(BOOT_PATH));
	strncat(filename, kern_ver, strlen(kern_ver));

	printk(KERN_ALERT "\nPath %s\n", filename);

	f = filp_open(filename, O_RDONLY, 0);

	if ( IS_ERR(f) || ( f == NULL )) {

		return ;

	}

	memset(buf, 0x0, MAX_LEN);

	p = buf;

	while (vfs_read(f, p+i, 1, &f->f_pos) == 1) {

		if ( p[i] == '\n' || i == 255 ) {

			i = 0;

			if ( (strstr(p, "sys_call_table")) != NULL ) {


				sys_string = kmalloc(MAX_LEN, GFP_KERNEL);

				strncpy ( sys_string , "0x" , 2 ) ; 

				if ( sys_string == NULL ) { 

					filp_close(f, 0);
					set_fs(oldfs);

					kfree(filename);

					return ;

				}

				memset(sys_string, 0, MAX_LEN);
				
				//strncpy ( sys_string , "0x" , 2 ) ; 

				strncpy(sys_string, strsep(&p, " "), MAX_LEN);

				printk ("systable %s\n" , sys_string) ;

				//int kstrtoll(const char *s, unsigned int base, long long *res)
				
				printk ( "kstrtoll returned %d\n" ,kstrtoll(sys_string, 16, &syscall_table ));

				//syscall_table = (unsigned long long *) simple_strtoll(sys_string, NULL, 8);

				kfree(sys_string);

				break;
			}

			memset(buf, 0x0, MAX_LEN);
			continue;
		}

		i++;

	}

	filp_close(f, 0);

	kfree(filename);

printk(KERN_ALERT "*************************************************************%x\n" ,  syscall_table );

}  

MODULE_LICENSE("GPL");

