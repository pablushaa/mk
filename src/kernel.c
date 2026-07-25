#include "drivers/ps2kb.h"
#include "drivers/txtm.h"
#include "drivers/timer.h"
#include "sys/idt.h"
#include "sys/pic.h"
#include "../config.h"
#include "util/convert.h"
#include "mm/mmap.h"
#include "mm/paging.h"
#include "mm/alloc.h"

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
