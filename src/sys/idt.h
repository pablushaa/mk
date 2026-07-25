#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <stddef.h>

#include "../drivers/timer.h"
#include "../drivers/ps2kb.h"
#include "../util/convert.h"
#include "../drivers/txtm.h"
#include "../mm/alloc.h"
#include "io.h"

void idt_init(void);
void idt_set_ent(uint8_t num, uint32_t handler, uint16_t selector, uint8_t flags);
void idt_handler(registers_t *regs);

#endif
