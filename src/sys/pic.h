#ifndef PIC_H
#define PIC_H

#include <stdint.h>

#include "io.h"

void pic_init(void);
void pic_en_irq(uint8_t irq);

#endif
