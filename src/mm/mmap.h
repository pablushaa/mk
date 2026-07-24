#ifndef MMAP_H
#define MMAP_H

#include <stdint.h>

void mmap_init(void);
uint32_t mmap_gfree_pages(void);
void mmap_set_used(uint32_t addr, uint32_t len);
void mmap_set_free(uint32_t addr, uint32_t len);

typedef struct {
        uint32_t addr_low;
        uint32_t addr_high;
        uint32_t len_low;
        uint32_t len_high;
        uint32_t type;
        uint32_t attr;
} __attribute__((packed)) e820_ent_t;

#endif
