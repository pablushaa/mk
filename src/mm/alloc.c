#include "alloc.h"

/* high-half kernel is cool!! */
static uint32_t heap_ptr = 0xC0000000 + 0x100000;

/* TODO: kaloviy kalloc. need to be rewritten some day */
/* allocates memory in kernel heap */
void*
kalloc(uint32_t size)
{
        void* ptr = (void*) heap_ptr;
        heap_ptr += size;
        return ptr;
}

void /* maybe later */
kfree(uint32_t* ptr) {}
