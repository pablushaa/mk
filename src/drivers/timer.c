#include "txtm.h"
#include "timer.h"
#include "../sys/io.h"
#include "../../config.h"
#include <stdint.h>

#define PIT_FREQ 1193182
#define PIT_CH0 0x40
#define PIT_CMD 0x43

uint32_t jiffies;

void
timer_init(uint16_t hz)
{
        jiffies = 0;
        uint16_t div = PIT_FREQ / hz;
        outb(PIT_CMD, 0x36);
        outb(PIT_CH0, div & 0xFF);
        outb(PIT_CH0, (div >> 8) & 0xFF);
}

void
timer_tick(registers_t* regs)
{
        jiffies++;
}

uint32_t
timer_get_jiff(void)
{
        return jiffies;
}

uint32_t
timer_gms(void)
{
        return (jiffies * 1000) / TIMER_HZ;
}

void
timer_sms(uint32_t ms)
{
        uint32_t target = jiffies + (ms * TIMER_HZ / 1000);
        while (jiffies < target)
        {
                asm volatile ("hlt");
        }
}
