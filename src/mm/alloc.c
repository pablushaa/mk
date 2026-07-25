#include "alloc.h"

static uint32_t heap_ptr = 0xC0000000 + 0x100000;

void*
kalloc(uint32_t size)
{
        void* ptr = (void*) heap_ptr;
        heap_ptr += size;
        return ptr;
}

void /* maybe later */
kfree(uint32_t* ptr) {}
