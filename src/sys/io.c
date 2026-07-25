#include "io.h"

/* cant say anything about this one */

uint8_t
inb(uint16_t port)
{
        uint8_t ret;
        __asm__ volatile ("inb %1, %0" : "=a"(ret) : "d"(port));
        return ret;
}

void
outb(uint16_t port, uint8_t val)
{
        __asm__ volatile ("outb %1, %0" : : "d"(port), "a"(val));
}

void
io_wait(void)
{
        outb(0x80, 0);
}
