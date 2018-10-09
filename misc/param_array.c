#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

/* $ cat /sys/module/param_array/parameters/array */
/* # echo "1,3,5,7" > /sys/module/param_array/parameters/array */

static short my_array[6] = {
    0,
    2,
    4,
    8,
};
static int my_size = 4;

void sleep_one_second(void)
{
	unsigned long j1;
    j1 = jiffies + HZ;

    while (time_before(jiffies, j1)) {
        schedule();
    }
}

static int __init test_init(void)
{
    int i;
    static int times = 0;

loop:
    for (i = 0; i < my_size; i++)
        printk(KERN_ALERT "my_array[%d]: %d\n", i, my_array[i]);
    sleep_one_second();
    
    if (times++ < 20)
        goto loop;

    return 0;
}

static void __exit test_exit(void)
{
}

module_init(test_init);
module_exit(test_exit);

module_param_array_named(array, my_array, short, &my_size, S_IRUGO | S_IWUSR);

MODULE_LICENSE("GPL");
