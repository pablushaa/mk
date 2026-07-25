#include "idt.h"

/* i hate idt so much
   this macro is writing 256
   extern isr functions */
#define VECTOR(n) extern void isr##n(void);
#include "vectors.inc"
#undef VECTOR

idt_ent_t* idt;
isr_t* isr_tbl;

/* initialise interrupt descriptor table */
void
idt_init(void)
{
        idt_ptr_t iptr;
        idt = (idt_ent_t*) kalloc(sizeof(idt_ent_t) * 256);
        isr_tbl = (void*) kalloc(sizeof(size_t) * 256);
        iptr.limit = 256 * 8 - 1;
        iptr.addr = (uint32_t) idt;

        /* this macro sets all 256 idt entries
           and points them to isr functions, provided by isr.s */
        #define VECTOR(n) idt_set_ent(n, (uint32_t)isr##n, 0x08, 0x8E);
        #include "vectors.inc"
        #undef VECTOR

        asm volatile ("lidt %0" : : "m"(iptr));
        isr_tbl[32] = timer_tick;
        isr_tbl[33] = ps2kb_intr;
}

/* filling one table entry
 when did osdev turn into filling tables? */
void
idt_set_ent(uint8_t num, uint32_t handler, uint16_t selector, uint8_t flags)
{
        idt[num].selector = selector;
        idt[num].off_low = handler & 0xFFFF;
        idt[num].off_high = (handler >> 16) & 0xFFFF;
        idt[num].zero = 0;
        idt[num].flags = flags;
}

/* every isr function calls this handler.
   i dont really want to write on asm */
void
idt_handler(registers_t *regs)
{
        if (regs->int_no < 32) {
                txtm_printks("err ");
                txtm_printks(itoa(regs->int_no, 10));
                for(;;) asm volatile("hlt");
        }

        if (regs->int_no >= 32 && regs->int_no < 48) {
                isr_tbl[regs->int_no](regs);

                if (regs->int_no >= 40) {
                        outb(0xA0, 0x20);
                        io_wait();
                }
                outb(0x20, 0x20);
                io_wait();
        }
}
