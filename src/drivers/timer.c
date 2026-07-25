#include "timer.h"

#define PIT_FREQ 1193182
#define PIT_CH0 0x40
#define PIT_CMD 0x43

uint32_t jiffies;

/* init timer at hz rate */
void
timer_init(uint16_t hz)
{
        jiffies = 0;
        uint16_t div = PIT_FREQ / hz;
        outb(PIT_CMD, 0x36);
        outb(PIT_CH0, div & 0xFF);
        outb(PIT_CH0, (div >> 8) & 0xFF);
}

/* timer interrupt, used in idt.h */
void
timer_tick(registers_t* regs)
{
        jiffies++;
}

/* get current jiffie */
uint32_t
timer_get_jiff(void)
{
        return jiffies;
}

/* get current ms */
uint32_t
timer_gms(void)
{
        return (jiffies * 1000) / TIMER_HZ;
}

/* sleep some ms */
void
timer_sms(uint32_t ms)
{
        uint32_t target = jiffies + (ms * TIMER_HZ / 1000);
        while (jiffies < target)
        {
                asm volatile ("hlt");
        }
}
