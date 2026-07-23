#include "drivers/txtm.h"
#include "sys/idt.h"
#include "sys/pic.h"

void
kernel(void)
{
        txtm_init_txtm();
        txtm_printks("+ kernel loaded\n");
        idt_init();
        txtm_printks("+ idt init\n");
        pic_init();
        pic_en_irq(0);
        pic_en_irq(1);
        pic_en_irq(2);
        txtm_printks("+ pic init\n");
        asm volatile ("sti");
        for(;;) { asm volatile("hlt"); }
}
