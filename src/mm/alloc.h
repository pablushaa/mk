#ifndef ALLOC_H
#define ALLOC_H

#include <stdint.h>
#include <stddef.h>

void* kalloc(size_t s);
void kfree(uint32_t* ptr);

#endif
