#include <linux/init.h>
#include <linux/module.h>
#include <linux/notifier.h>

static RAW_NOTIFIER_HEAD(test_chain);

int test_notifier_register(struct notifier_block *nb)
{
	return raw_notifier_chain_register(&test_chain, nb);
}
EXPORT_SYMBOL(test_notifier_register);

int test_notifier_unregister(struct notifier_block *nb)
{
	return raw_notifier_chain_unregister(&test_chain, nb);
}
EXPORT_SYMBOL(test_notifier_unregister);

int call_test_notifiers(int val, void *v)
{
	return raw_notifier_call_chain(&test_chain, val, v);
}
EXPORT_SYMBOL(call_test_notifiers);
