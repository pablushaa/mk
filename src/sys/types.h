#ifndef TYPES_H
#define TYPES_H

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

typedef void (*isr_t)(registers_t* regs);

typedef struct {
        uint32_t addr_low;
        uint32_t addr_high;
        uint32_t len_low;
        uint32_t len_high;
        uint32_t type;
        uint32_t attr;
} __attribute__((packed)) e820_ent_t;

#endif
