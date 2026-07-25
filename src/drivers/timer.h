#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#include "../../config.h"
#include "../sys/types.h"
#include "../sys/io.h"

void timer_init(uint16_t hz);
void timer_tick(registers_t* regs);
void timer_sms(uint32_t ms);
uint32_t timer_gms(void);


#endif
