#include "gdt.h"

gdt_ent_t gdt[6];
tss_t tss = {0};

void
gdt_init(void)
{
        tss.esp0 = 0x100000;
        tss.ss0 = 0x10;

        gdt[0] = (gdt_ent_t) {0, 0, 0, 0, 0, 0};
        gdt[1] = (gdt_ent_t) {0xFFFF, 0, 0, 0b10011010, 0b11001111, 0};
        gdt[2] = (gdt_ent_t) {0xFFFF, 0, 0, 0b10010010, 0b11001111, 0};
        gdt[3] = (gdt_ent_t) {0xFFFF, 0, 0, 0b11111010, 0b11001111, 0};
        gdt[4] = (gdt_ent_t) {0xFFFF, 0, 0, 0b11110010, 0b11001111, 0};

        uint32_t base = (uint32_t) &tss;
        uint32_t limit = sizeof(tss_t) - 1;

        gdt[5].limit_low = limit & 0xFFFF;
        gdt[5].base_low = base & 0xFFFF;
        gdt[5].base_mid = (base >> 16) & 0xFF;
        gdt[5].acc = 0b10001001;
        gdt[5].flags = 0x40;
        gdt[5].base_high = (base >> 24) & 0xFF;

        gdt_ptr_t ptr;
        ptr.limit = sizeof(gdt) - 1;
        ptr.base = (uint32_t) gdt;

        asm volatile ("lgdt %0" : : "m"(ptr));

        asm volatile (
                "mov $0x10, %%ax\n"
                "mov %%ax, %%ds\n"
                "mov %%ax, %%es\n"
                "mov %%ax, %%fs\n"
                "mov %%ax, %%gs\n"
                "mov %%ax, %%ss\n"
                "ljmp $0x08, $1f\n"
                "1:\n"
                : : : "memory"
        );

        asm volatile ("ltr %0" : : "r" (0x28));
}
