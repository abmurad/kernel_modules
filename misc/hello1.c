#include <linux/init.h>
#include <linux/module.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter/xt_owner.h>

static bool hello_mt(const struct sk_buff *skb,
		struct xt_action_param *par)
{
	if (in_interrupt())
		pr_info("In interrupt\n");
	else
		pr_info("Not in interrupt\n");

	pr_info("par->in=%p/out=%p fam=%d bytes=%d\n",
		par->in, par->out, par->family, skb->len);

	return true;
}

static struct xt_match hello_reg __read_mostly = {
	.name = "owner",
	.revision = 1,
	.family = NFPROTO_UNSPEC,
	.match = hello_mt,
	.matchsize = sizeof(struct xt_owner_match_info),
	.me = THIS_MODULE,
};

static int __init hello_init(void)
{
	return xt_register_match(&hello_reg);
}

static void __exit hello_exit(void)
{
	xt_unregister_match(&hello_reg);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
