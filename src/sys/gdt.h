#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#include "types.h"

extern tss_t tss;
void gdt_init(void);

#endif
