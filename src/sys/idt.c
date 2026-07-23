#include "io.h"
#include "idt.h"
#include "../util/convert.h"
#include "../drivers/txtm.h"
#include "../drivers/timer.h"
#include "../drivers/ps2kb.h"

idt_ent_t idt[256];

/* i hate idt so much */
#define VECTOR(n) extern void isr##n(void);
#include "vectors.inc"
#undef VECTOR

void
idt_init(void)
{
        idt_ptr_t iptr;
        iptr.limit = 256 * 8 - 1;
        iptr.addr = (uint32_t) idt;
        #define VECTOR(n) idt_set_ent(n, (uint32_t)isr##n, 0x08, 0x8E);
        #include "vectors.inc"
        #undef VECTOR
        asm volatile ("lidt %0" : : "m"(iptr));
}

void
idt_set_ent(uint8_t num, uint32_t handler, uint16_t selector, uint8_t flags)
{
        idt[num].selector = selector;
        idt[num].off_low = handler & 0xFFFF;
        idt[num].off_high = (handler >> 16) & 0xFFFF;
        idt[num].zero = 0;
        idt[num].flags = flags;
}

void
idt_handler(registers_t *regs)
{
        if (regs->int_no < 32) {
                txtm_printks("EXCEPTION: Unhandled exception ");
                txtm_printks(itoa(regs->int_no, 10));
                for(;;) asm volatile("hlt");
        }

        if (regs->int_no >= 32 && regs->int_no < 48) {
                if (regs->int_no == 32) { timer_tick(); }
                if (regs->int_no == 33) { ps2kb_intr(); }

                if (regs->int_no >= 40) {
                        outb(0xA0, 0x20);
                        io_wait();
                }
                outb(0x20, 0x20);
                io_wait();
        }
}
