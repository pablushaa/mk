#ifndef CONVERT_H
#define CONVERT_H

#include <stdint.h>

static const char* n10 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char* itoa(uint32_t n, uint8_t base);

#endif
