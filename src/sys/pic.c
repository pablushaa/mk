#include "pic.h"

void
pic_init(void)
{
        /* starting init */
        outb(0x20, 0x11);
        io_wait();
        outb(0xA0, 0x11);
        io_wait();

        /* vector remap: irq0-7 -> vector 0x20-0x27
         *                        irq8-15 -> vector 0x28-0x2F */
        outb(0x21, 0x20);
        io_wait();
        outb(0xA1, 0x28);
        io_wait();

        /* cascade connection */
        outb(0x21, 0x04);
        io_wait();
        outb(0xA1, 0x02);
        io_wait();

        /* 8086 mode */
        outb(0x21, 0x01);
        io_wait();
        outb(0xA1, 0x01);
        io_wait();

        /* masking everything */
        outb(0x21, 0xFF);
        outb(0xA1, 0xFF);
}

void
pic_en_irq(uint8_t irq)
{
        uint16_t port;
        uint8_t value;

        if (irq < 8) port = 0x21;
        else {port = 0xA1; irq -= 8; }

        value = inb(port);
        value &= ~(1 << irq);
        outb(port, value);
}
