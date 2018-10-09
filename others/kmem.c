#include	<linux/init.h>

#include	<linux/module.h>

#include	<linux/slab.h>

#include	<linux/mm.h>

#include	<linux/vmalloc.h>

#include	<linux/mm_types.h>

#include	<asm/topology.h>

#include	<asm/pgtable.h>

#include	<asm/io.h>

#include	<asm/page.h>

#define MEM

//#define GFP

//#define KMEM

//#define ALLOC_PAGE

//#define VMALLOC

typedef struct kmem_cache kmem_cache_t ;

kmem_cache_t *cache_object = NULL ;

int init_module()
{

	#ifdef KMEM 

	cache_object = kmem_cache_create ( "freakZ" , 4096 * 4 , 0 , SLAB_HWCACHE_ALIGN , NULL  ) ;

	if ( ! cache_object ) {

		printk("slab allocatio failed\n");

		return 1 ;

	}
	
	void *ptr = NULL ;

	ptr = kmem_cache_alloc ( cache_object , GFP_KERNEL ) ;

	if ( ! ptr ) {

                printk("slab allocatio failed\n");

                return 1 ;

        }

	kmem_cache_free ( cache_object , ptr ) ;

	#endif

	#ifdef GFP

	unsigned long addr ;

	addr = get_zeroed_page ( __GFP_HIGHMEM ) ;

	printk ("get_zeroed_page returned %x\n" , addr);

	free_page ( addr ) ;

	addr = __get_free_page ( GFP_KERNEL ) ;

	printk ("__get_free_page returned %x\n" , addr);

	free_page ( addr ) ;

	addr = __get_free_pages ( GFP_KERNEL  , 2 ) ;

	printk ("__get_free_pages returned %x\n" , addr);

	free_pages  ( addr , 2 ) ;
	
	#endif
	
	#ifdef ALLOC_PAGE 

	printk("current numa id %d\n" , numa_node_id());

	struct page *page = NULL ;

	page = alloc_pages_node ( numa_node_id() , GFP_KERNEL , 0 ) ;

	printk ("alloc_pages_node returned %x\n" , page) ;

	__free_page( page ) ;

	page = NULL ;

	page = alloc_pages ( GFP_KERNEL , 0 ) ;

	printk ("alloc_pages returned %x\n" , page) ;

        __free_pages( page , 0  ) ;

	#endif

	#ifdef VMALLOC

	printk (" VMALLOC_START %x VMALLOC_END %x \n" , VMALLOC_START   , VMALLOC_END) ;

	void *addr = NULL ;

	addr = vmalloc( 1024 ) ;

	printk ("vmalloc has returned %x\n" , addr) ;

	vfree( addr ) ;

	#endif

	//outb(0x64 , 22);
	
	#ifdef MEM

	printk ("PAGE_SIZE %d PAGE_SHIFT %d\n" , PAGE_SIZE , PAGE_SHIFT ) ;

	struct page *virt_to_page ( void *kaddr ) ;

	#endif

	return 0 ;

}

void cleanup_module()
{
	kmem_cache_destroy( cache_object ); 

	return ;

}
