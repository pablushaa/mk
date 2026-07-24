#include "drivers/ps2kb.h"
#include "drivers/txtm.h"
#include "drivers/timer.h"
#include "sys/idt.h"
#include "sys/pic.h"
#include "../config.h"
#include "util/convert.h"
#include "mm/mmap.h"
#include "mm/paging.h"

#define TO_STR(x) #x
#define STR(x) TO_STR(x)

void
kernel(void)
{
        txtm_init_txtm();
        txtm_printks("+ kernel " KERNEL_NAME " (" KERNEL_GIT ") loaded \n");
        idt_init();
        txtm_printks("+ idt init\n");
        pic_init();
        pic_en_irq(0);
        pic_en_irq(1);
        txtm_printks("+ pic init\n");
        timer_init(TIMER_HZ);
        txtm_printks("+ timer init at " STR(TIMER_HZ) " hz\n");
        asm volatile ("sti");
        mmap_init();
        paging_init();
        txtm_printks("+ paging init\n");
        txtm_printks(itoa(mmap_gfree_pages(), 10));
        txtm_printks(" pages free");
        for(;;) { }
}
