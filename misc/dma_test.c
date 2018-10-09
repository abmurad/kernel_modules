#include <linux/init.h>
#include <linux/module.h>
#include <linux/dmaengine.h>

static int __init test_init(void)
{
	//struct dma_chan *dc = dma_find_channel(DMA_MEMCPY);
	struct dma_chan *dc = dma_find_channel(DMA_ASYNC_TX);
	if (dc) {
		pr_info("get channel\n");
	} else
		pr_err("No channel\n");

	return 0;
}

static void __exit test_exit(void)
{
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
