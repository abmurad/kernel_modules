#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sysinfo.h>
extern int sysinfo (struct sysinfo *__info) ;

int init_module(void)
{
    int k;
    struct sysinfo info;
    printk(KERN_INFO "hello\n");
    k = sysinfo(&info);
    printk(KERN_EMERG "procs = %d\n", info.procs);

    return 0;
}

void cleanup_module(void)
{

    printk(KERN_INFO "Goodbye\n");
}
