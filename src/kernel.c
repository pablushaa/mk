#include "drivers/timer.h"
#include "drivers/txtm.h"
#include "util/convert.h"
#include "../config.h"
#include "sys/idt.h"
#include "sys/pic.h"
#include "mm/paging.h"
#include "mm/mmap.h"

/* main kernel function. for now, it is a garbage */

void
kernel(void)
{
        txtm_init_txtm();
        txtm_printks("+ kernel " KERNEL_NAME " (#" KERNEL_GIT ") loaded \n");
        mmap_init();
        paging_init();
        txtm_printks("+ mem init: ");
        txtm_printks(itoa(mmap_gfree_pages() / 254, 10));
        txtm_printks(" mb free\n");
        idt_init();
        pic_init();
        pic_en_irq(0);
        pic_en_irq(1);
        asm volatile ("sti");
        txtm_printks("+ idt inited & pic enabled\n");
        timer_init(TIMER_HZ);
        for(;;) {}
}
