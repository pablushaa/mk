#ifndef PS2KB_H
#define PS2KB_H

#include <stdint.h>

#include "../util/convert.h"
#include "../sys/types.h"
#include "../sys/io.h"
#include "txtm.h"

void ps2kb_intr(registers_t *regs);

#endif
