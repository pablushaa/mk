#include "convert.h"

/* there had to be only 10 digits, but uuuh*/
static const char* n10 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char* itoa(uint32_t n, uint8_t base)
{
        static char buf[33];

        int i = 32;
        buf[i] = '\0';

        if (n == 0) {
                buf[--i] = '0';
        } else {
                while (n > 0) {
                        buf[--i] = n10[n % base];
                        n /= base;
                }
        }

        return &buf[i];
}
