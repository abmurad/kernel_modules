#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x505ab3ea, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x757f958c, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0x7b691e5, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0xb5a459dc, __VMLINUX_SYMBOL_STR(unregister_blkdev) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9664d782, __VMLINUX_SYMBOL_STR(blk_cleanup_queue) },
	{ 0x1f6b33ca, __VMLINUX_SYMBOL_STR(device_add_disk) },
	{ 0x772bebd1, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0x9d82d59d, __VMLINUX_SYMBOL_STR(blk_init_queue) },
	{ 0xa202a8e5, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x51fc6155, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x1cf6cdb3, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x71a50dbc, __VMLINUX_SYMBOL_STR(register_blkdev) },
	{ 0xb44ad4b3, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x868ff6c2, __VMLINUX_SYMBOL_STR(__blk_end_request_cur) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x36c9ee83, __VMLINUX_SYMBOL_STR(blk_fetch_request) },
	{ 0x69acdf38, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7FF74C7882C09AAE163EF00");
