#ifndef PS2KB_H
#define PS2KB_H

#include <stdint.h>
#include "../sys/idt.h"

void ps2kb_intr(registers_t *regs);

#endif
