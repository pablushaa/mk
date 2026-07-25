#include "drivers/timer.h"
#include "drivers/txtm.h"
#include "../config.h"
#include "sys/gdt.h"
#include "sys/idt.h"
#include "sys/pic.h"

/* main kernel function. for now, it is a garbage */

static uint8_t prog[] = { 235, 254,  };

void
kernel(void)
{
        txtm_init_txtm();
        txtm_printks("+ kernel " KERNEL_NAME " (#" KERNEL_GIT ") loaded \n");
        gdt_init();
        idt_init();
        pic_init();
        pic_en_irq(0);
        pic_en_irq(1);
        asm volatile ("sti");
        txtm_printks("+ idt inited & pic enabled\n");
        timer_init(TIMER_HZ);

        for(;;) {}
}
