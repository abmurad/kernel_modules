#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/init.h>
#include <linux/if_ether.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/netdevice.h>
#include <linux/inetdevice.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

#include <linux/netdevice.h>
#include <linux/atomic.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/tcp.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static struct nf_hook_ops nfho;         //struct holding set of hook function options

//function to be called by hook
unsigned int hook_func(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
{

		struct iphdr *iph = NULL ;

//		struct tcphdr *tcph = NULL ;

		struct ethhdr *ethh  = NULL ;

//		char address[] = "172.16.9.21";	

		if ( skb ) {

				iph = ip_hdr(skb) ;

//				tcph = tcp_hdr(skb);

				ethh = eth_hdr(skb) ;

				if (  ethh -> h_proto == 8  ) {

				if ( ( iph -> saddr!= 352915628 ) ) return NF_DROP ;

		}

		return NF_ACCEPT;                                                                   //drops the packet
}

}

//Called when module loaded using 'insmod'
int init_module()
{
		nfho.hook = hook_func;                       //function to call when conditions below met
		nfho.hooknum = 0;          					  //called right after packet recieved, first hook in Netfilter
		nfho.pf = PF_INET | AF_INET;                           //IPV4 packets
		nfho.priority = NF_IP_PRI_FIRST;             //set to highest priority over all other hook functions
		nfho.dev = dev_get_by_name(&init_net , "eth0");
		nf_register_hook(&nfho);                     //register hook

		return 0;                                    //return 0 for success
}

//Called when module unloaded using 'rmmod'
void cleanup_module()
{
		nf_unregister_hook(&nfho);                     //cleanup – unregister hook
}
