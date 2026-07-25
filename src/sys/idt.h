#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct
{
        uint16_t limit;
        uint32_t addr;
} __attribute__((packed)) idt_ptr_t;

typedef struct
{
        uint16_t off_low;
        uint16_t selector;
        uint8_t  zero;
        uint8_t  flags;
        uint16_t off_high;
} __attribute__((packed)) idt_ent_t;

typedef struct {
        uint32_t gs, fs, es, ds;
        uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
        uint32_t int_no, err_code;
        uint32_t eip, cs, eflags;
} __attribute__((packed)) registers_t;

typedef void (*isr_t)(void);

void idt_init(void);
void idt_set_ent(uint8_t num, uint32_t handler, uint16_t selector, uint8_t flags);
void idt_handler(registers_t *regs);

#endif
