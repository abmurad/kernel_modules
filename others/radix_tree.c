

//cd /sys/modules/

#include <linux/init.h>
#include <linux/tty.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/ptrace.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/threads.h>
#include <asm/kmap_types.h>
#include <asm/tlbflush.h>
#include <asm/paravirt.h>
#include <asm/fixmap.h>
#include <linux/device.h>
#include <linux/mm_types.h>
#include <asm/page.h>
#include<asm/pgtable.h>
#include<linux/fdtable.h>
#include <linux/slab.h>

#include <linux/highmem.h>

MODULE_LICENSE ("Dual BSD/GPL");

#define FIRST_MINOR	10
#define NR_DEVS 1	//	Number of device numbers


int myOpen (struct inode *inode,struct file *filep);
int myRelease (struct inode *in,struct file *fp);
#define GPF_DISABLE write_cr0(read_cr0() & (~ 0x00010000))
#define GPF_ENABLE write_cr0(read_cr0() | 0x00010000)
long myioctl(struct file *, unsigned int, long unsigned int);
//long myioctl(int xx, unsigned int, long unsigned int);
static int myInit (void);
static void myExit (void);
void *kmap(struct page *page);

struct file_operations fops = { //For required file operations
	 owner	        : THIS_MODULE,
	 open	        : myOpen,
	 release        : myRelease,
	 unlocked_ioctl : myioctl
};

char *devname;
int majNo;
static dev_t mydev;
struct cdev *my_cdev;
int kill = 0 ;

module_param (devname, charp, 0000);//to accept the command_line arguments
module_param (kill, int, 0644);//to accept the command_line arguments

static struct class *mychar_class;
static struct device *mychar_device;
struct file_opearions *fortty = NULL ;

int myOpen (struct inode *inode, struct file *filep)
{	
	printk (KERN_DEBUG "Open successful\n");
	return 0;
}

int write_console (char *str)
        {
         struct tty_struct *my_tty;
         if((my_tty=current->signal -> tty) != NULL)
                {
		printk ("%p\n" , (my_tty->driver -> ops -> write)(my_tty , "uma\n" , 4) ) ;
		//printk ("%p\n" , fortty -> write ) ;
//                (*(my_tty->driver) . write) (my_tty,0, "umaraju",7 );
                return 0;
                }
         else return -1;
        }


long myioctl(struct file* filp, unsigned int x, long unsigned int var ) 

{
	struct task_struct *task = current;//To get the current process running 
//	printk("height of radix tree is %d\n" , (task -> files -> fdt ->fd[3] -> f_mapping -> host -> i_mapping ->  page_tree .  height )) ;
#if 1


	asm volatile ( "mov %%cr3 , %0": "=r"(var) );

	var = mem_map ;

	write_console ("nothing") ;

	printk ("physical address is %p page offset is %x\n" , var , PAGE_OFFSET );
	
	var = current -> mm -> pgd ;

	pgd_t *pgd_addr  = NULL;
	pte_t *pte_addr = NULL;
	pte_t pte_temp = (pte_t)var;
	pgd_t *pgd_addr_var ;
	pte_t *pte_addr_var ;
	unsigned long off_pgd = 0 ;
	unsigned long off_pte = 0 ;
	unsigned long off_page = 0 ;
	unsigned long page_address = 0 ;
	unsigned long page_address_offset = 0 ;

	printk ("size of struct page is %zu\n" , sizeof ( struct page ) ) ;

	void *address = (task -> files -> fdt ->fd[3] -> f_mapping -> host -> i_mapping ->  page_tree .  rnode -> slots[0]);

//	printk("address of slot 0 %p\n" , *(int*)address );

	printk("height of radix tree is %d\n" , (task -> files -> fdt ->fd[3] -> f_mapping -> host -> i_mapping ->  page_tree .  height )) ;

/*	pgd_addr  = task -> mm -> pgd ;

	off_pgd = var >> 22 ;

	pgd_addr_var = ( pgd_t* )((unsigned int*)pgd_addr + off_pgd) ;

	pte_addr = kmap ( mem_map + ( ( (unsigned int) pgd_addr_var -> pgd ) >> 12 ) ) ;

	off_pte = ( var & 0x003ff000 ) ;

	pte_addr_var = (pte_t*) ( (unsigned int*) pte_addr + ( ( off_pte ) >> 12 ) ) ;

	page_address = (unsigned) kmap ( mem_map + ( ( (unsigned int) pte_addr_var -> pte ) >> 12 ) ) ;

	printk ("address your lokking for is %p\n" , pte_addr_var -> pte ) ;
*/
	/*off_page = var & 0x00000fff ;

	page_address_offset =  page_address + off_page ;

	if ( *(unsigned int*) page_address_offset == x ) {

		printk ("good job page walk is successful\n") ;

		*(unsigned int*) page_address_offset = 199 ;

	}*/
#endif
	return 0;
}

int myRelease (struct inode *in, struct file *fp)
{
	printk (KERN_INFO "File released \n");
	return 0;
}

static int __init myInit (void)
{
	int ret	=	-ENODEV;
	int status;


	if ( devname == NULL ) {

		printk ("you've missed command line argument \n");

		return  0;

	}

	printk (KERN_INFO "Initializing Character Device \n");

	status	=	alloc_chrdev_region (&mydev, FIRST_MINOR, NR_DEVS, devname);

	if (status < 0)
	{
		printk (KERN_NOTICE "Device numbers allocation failed: %d \n",status);
		goto err;
	}

	printk (KERN_INFO "Major number allocated = %d \n",MAJOR(mydev));
	my_cdev	=	cdev_alloc ();

	if (my_cdev == NULL) {
		printk (KERN_ERR "cdev_alloc failed \n");
		goto err_cdev_alloc;
	}

	cdev_init (my_cdev, &fops);
	my_cdev->owner	=	THIS_MODULE;

	//The kernel maintains a list of character devices under cdev_map
	status	=	cdev_add (my_cdev, mydev, NR_DEVS); //cdev_add registers a character device with the kernel. 
	if (status) {
		printk (KERN_ERR "cdev_add failed \n");
		goto err_cdev_add;
	}

	mychar_class	=	class_create (THIS_MODULE, devname);
	if (IS_ERR(mychar_class)) {
		printk (KERN_ERR "class_create() failed \n");
		goto err_class_create;
	}

	mychar_device =	device_create (mychar_class, NULL, mydev, NULL, devname);
	if (IS_ERR(mychar_device)) {
		printk (KERN_ERR "device_create() failed \n");
		goto err_device_create;
	}

	return 0;

err_device_create:
	class_destroy (mychar_class);

err_class_create:
	cdev_del(my_cdev);

err_cdev_add:
	kfree (my_cdev);

err_cdev_alloc:

	unregister_chrdev_region (mydev, NR_DEVS);

err:
	return ret;
}


static void myExit (void)
{
	printk (KERN_INFO "Exiting the Character Driver \n");

	device_destroy (mychar_class, mydev);
	class_destroy (mychar_class);
	cdev_del (my_cdev);
	unregister_chrdev_region (mydev, NR_DEVS);

	return;
}

module_init (myInit);
module_exit (myExit);

