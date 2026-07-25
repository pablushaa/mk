#include "paging.h"
#include "mmap.h"

void
paging_init(void)
{
        /* allocating frame for page directory */
        uint32_t cr0;
        uint32_t* page_dir_phy = (uint32_t*) mmap_alloc_frame();
        for (int i = 0; i < 1024; i++) page_dir_phy[i] = 0;

        /* allocating page table */
        uint32_t* page_tabl_phy = (uint32_t*) mmap_alloc_frame();
        for (int i = 0; i < 1024; i++) page_tabl_phy[i] = (i << 12) | 0x03;

        /* kernel heap */
        uint32_t* kheap_tabl_phy = (uint32_t*) mmap_alloc_frame();
        for (int i = 0; i < 1024; i++)
        {
                uint32_t phys_addr = (i * 4096) + 0x400000;
                kheap_tabl_phy[i] = phys_addr | 0x03;
        }

        page_dir_phy[0] = ((uint32_t)page_tabl_phy) | 0x03; /* r0, present, rw */
        page_dir_phy[768] = ((uint32_t)kheap_tabl_phy) | 0x03; /* r0, present, rw */

        asm volatile ("mov %0, %%cr3" : : "r"((uint32_t)page_dir_phy));
        asm volatile ("mov %%cr0, %0" : "=r"(cr0));
        cr0 |= 0x80000000;
        asm volatile ("mov %0, %%cr0" : : "r"(cr0));
        asm volatile("jmp 1f\n" "1:" );
}
