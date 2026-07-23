#ifndef PIC_H
#define PIC_H

#include "io.h"
#include <stdint.h>

void pic_init(void);
void pic_en_irq(uint8_t irq);

#endif
