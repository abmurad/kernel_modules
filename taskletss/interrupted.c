#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/hrtimer.h>
#include <linux/sched.h>
#include <linux/time.h>
struct irq_info
{
	int irq_num;
	int count_irq;
}irq_data;

static struct work_struct wq ;

static void tasklet_handler(unsigned long);
DECLARE_TASKLET(tasklet, tasklet_handler,(unsigned long) &irq_data);

static void tasklet_handler(unsigned long irq_data)
{
	struct timeval time;

	do_gettimeofday(&time);
	printk(KERN_INFO "Tasklet handler triggerd \n") ;
}

irqreturn_t int_handler(int irq, void *dev_id, struct pt_regs *regs)
{
	struct timeval time;

	do_gettimeofday(&time);
        irq_data.count_irq++;
          
        printk(KERN_INFO "Interrupt has triggerd at %08u.%06u\n",(int)(time.tv_sec % 100000000), (int)(time.tv_usec));

//	tasklet_schedule(&tasklet);

	schedule_work(&wq) ;

        return IRQ_HANDLED;
}
static int __init init_proc(void)
{
        int ret;
        ret = request_irq(1, int_handler, IRQF_SHARED, "Interrupt", int_handler);
        if (ret==0)
                printk(KERN_INFO "my interrupt module is initialized \n");
        else
                printk(KERN_INFO "my interrupt module's initialization failed | error_code=%i\n", ret);

	INIT_WORK(&wq , ( void(*)(void *)) tasklet_handler );
        
	return 0;
}
static void __exit exit_proc(void)
{
        free_irq(1, int_handler);
        printk(KERN_INFO "Interrupt Module destroyed \n");
}
module_init(init_proc);
module_exit(exit_proc);

MODULE_LICENSE("GPL");
