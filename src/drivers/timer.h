#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_init(uint16_t hz);
void timer_tick(void);
void timer_sms(uint32_t ms);
uint32_t timer_gms(void);


#endif
