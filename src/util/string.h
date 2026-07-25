#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* dest, uint8_t val, size_t n);

#endif
