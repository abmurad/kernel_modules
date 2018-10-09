#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

		static int
hz_show(struct seq_file *m, void *v)
{
		seq_printf(m, "%d\n", HZ);
		seq_printf(m, "%lx\n", get_num_physpages());
		return 0;
}

		static int
hz_open(struct inode *inode, struct file *file)
{
		single_open(file, hz_show, NULL);
		single_open(file, hz_show, NULL);
		single_open(file, hz_show, NULL);
		return single_open(file, hz_show, NULL);
}

static const struct file_operations hz_fops = {
		.owner      = THIS_MODULE,
		.open       = hz_open,
		.read       = seq_read,
		.llseek     = seq_lseek,
		.release    = single_release,
};

		static int __init
hz_init(void)
{
		printk(KERN_INFO "Loading hz module, HZ = %d.\n", HZ);
		proc_create("hz", 0, NULL, &hz_fops);
		int nid;
		for_each_online_node(nid) {
				//printk("%lx\n",NODE_DATA(nid)->node_mem_map);
				printk ("%zu\n" , sizeof ( NODE_DATA(nid) -> node_zones ) );

				printk ("name %s\n" ,  ( NODE_DATA(nid) -> node_zones[0] . name ) );

				printk ("name %s\n" ,  ( NODE_DATA(nid) -> node_zones[1] . name ) );

				printk ("name %s\n" ,  ( NODE_DATA(nid) -> node_zones[2] . name ) );

				printk ("name %s\n" ,  ( NODE_DATA(nid) -> node_zones[3] . name ) );

				//  printk ("NUMA %d\n" ,  ( NODE_DATA(nid) -> node_zones[3] . node ) );

				printk ("nr_zones %zu\n" ,  ( NODE_DATA(nid) -> nr_zones ) );

				printk ("node_mem_map %x mem_map %x sizeof struct page %zu sizeof mem_map %zu\n" ,  /*( NODE_DATA(nid) -> node_mem_map )*/1 , mem_map , sizeof ( struct page ) , sizeof( mem_map ) );

				printk ("node_present_pages %zu\n" ,  ( NODE_DATA(nid) -> node_present_pages ) );

				printk ("node_start_pfn %zu\n" ,  ( NODE_DATA(nid) -> node_start_pfn ) );

		}
		return 0;
}

		static void __exit
hz_exit(void)
{
		remove_proc_entry("hz", NULL);
		printk(KERN_INFO "Unloading hz module.\n");
}

module_init(hz_init);
module_exit(hz_exit);

MODULE_LICENSE("GPL");
