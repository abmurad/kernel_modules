#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>


MODULE_LICENSE ("Dual BSD/GPL");

#define FIRST_MINOR 10  // minor number should start from 10
#define NR_DEVS 1  // Number of device numbers


int myOpen (struct inode *inode,struct file *filep);
int myRelease (struct inode *in,struct file *fp);
//long myIoctl(int fd);
long myIoctl(int fd,unsigned int cmd , char *ptr );
//long myIoctl(int fd,unsigned int cmd ,unsigned long x);
void path(struct dentry *d);
static int myInit (void);
static void myExit (void);
static inline void _get_fs_root(struct fs_struct *fs, struct path *root)
{
  //  *root = fs->root;
//    path_get(root);
}
//EXPORT_SYMBOL(get_fs_root);
static inline void _get_fs_pwd(struct fs_struct *fs, struct path *pwd)
{
    //*pwd = fs->pwd;
    //path_get(pwd);
}


struct file_operations fops = {  // registration to kernel
		.owner = THIS_MODULE,
		.open =	myOpen,
		.unlocked_ioctl = myIoctl,
		.release = myRelease
};

char *devname;
int majNo;
static dev_t mydev;
struct cdev *my_cdev;

module_param (devname, charp, 0000);

static struct class *mychar_class;
static struct device *mychar_device;


int myOpen (struct inode *inode, struct file *filep)
{	
	printk ( "Open successful\n");
	return 0;

}
/******IOCTL*******/

static int c_init(void)
{

 char *cwd;
        struct path pwd, root;

 pwd = current->fs->pwd;

 path_get(&pwd);

 root=  current->fs->root;

 path_get(&root);

 char *buf = (char *)kmalloc(GFP_ATOMIC,100*sizeof(char));

 cwd = d_path(&current -> fs -> pwd ,buf,100*sizeof(char));
/// printk(KERN_ALERT "Hello,the current working directory is \n %s",cwd);

 return 0;
}

	
//long myIoctl(int fd,unsigned int cmd, unsigned long xx )
long myIoctl(int fd , unsigned int cmd , char *ptr )
{
//	c_init();
	#if 0
	struct task_struct *task = current;
        
	int flag;
	
	struct vm_area_struct *temp = task -> mm -> mmap;
	
	while ( temp ) {

            printk ("%08x ", temp -> vm_start);
        
	    printk  ("- ");
        
	    printk  ("%08x   ",(unsigned int) temp -> vm_end);
        
	    flag = ((temp -> vm_flags) & ((1 << 4) -1 )) ;
        
	    if ((flag & VM_READ) == VM_READ)
        
		        printk ("r");
        
	    else
               	
			printk ("-");

        if ((flag & VM_WRITE) == VM_WRITE)
             
			   printk ("w");
             
	    else

              printk ("-");


        if((flag & VM_EXEC) == VM_EXEC)

              printk ("x");

        else
              printk ("-");
  

	    if ((flag & VM_SHARED) == VM_SHARED)
        	
   	        printk ("s");

        else
                
			printk ("p");
   
        printk ("\t");
       
	    if (temp -> vm_file != NULL)
            
	       printk ("%08x  ",(unsigned int) (temp -> vm_pgoff) << 12);

        else
            
	       printk ("%08x",(unsigned int) temp -> vm_file);

        printk ("\t");
	   
	    if ( temp -> vm_file != NULL) {
           
	 	unsigned int t = temp -> vm_file -> f_path.dentry -> d_sb -> s_dev;

      		printk ("0%0d "  , MAJOR(t) );

			printk (":");

			printk (" 0%d", MINOR(t));

       		printk ("  %ld  ", temp -> vm_file -> f_inode -> i_ino);

			path(temp -> vm_file -> f_path.dentry);
	    }

	   else {
			printk ("00 ");
       		printk (":");
      		printk (" 00");
       		printk ("  0");
	   } 
   
      printk ("\n");

      temp = temp -> vm_next ;
  
  	}
#endif
	return 0 ;
}

void path(struct dentry *d){
	
	printk("***********%s %s****************\n" , d -> d_name.name , d -> d_parent -> d_name . name );
	if ((d -> d_parent) != (d)){

			path (d -> d_parent);

			//printk ("/%s",d -> d_name.name);
	}else 
	printk("***********%s %s****************\n" , d -> d_name.name , d -> d_parent -> d_name . name );

}


int myRelease (struct inode *in, struct file *fp)
{
	printk (KERN_INFO "File released \n");
	return 0;
}

static int __init myInit (void)
{
	int ret	= -ENODEV;
	int status;

	printk ( "Initializing Character Device \n");

	status	=	alloc_chrdev_region (&mydev, FIRST_MINOR, NR_DEVS, devname);

	if (status < 0)
	{
		printk ( "Device numbers allocation failed: %d \n",status);
		goto err;
	}

	printk ( "Major number allocated = %d \n",MAJOR(mydev));
	my_cdev	=	cdev_alloc ();

	if (my_cdev == NULL) {
	
		printk ( "cdev_alloc failed \n");
		goto err_cdev_alloc;
	}

	cdev_init (my_cdev, &fops);
	my_cdev->owner	=	THIS_MODULE;

	status	=	cdev_add (my_cdev, mydev, NR_DEVS);
	
	if (status) {
	
		printk (KERN_ERR "cdev_add failed \n");
		goto err_cdev_add;
	}

	mychar_class	=	class_create (THIS_MODULE, devname);

	if (IS_ERR(mychar_class)) {
	
		printk ("class_create() failed \n");
		goto err_class_create;
	}

	mychar_device =	device_create (mychar_class, NULL, mydev, NULL, devname);

	if (IS_ERR(mychar_device)) {
	
		printk ("device_create() failed \n");
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
	printk ("Exiting the Character Driver \n");

	device_destroy (mychar_class, mydev);
	class_destroy (mychar_class);
	cdev_del (my_cdev);
	unregister_chrdev_region (mydev, NR_DEVS);

	return;
}

module_init (myInit); // macros provided by the kernel
module_exit (myExit);
