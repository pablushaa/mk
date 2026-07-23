#include "convert.h"

char* itoa(uint32_t n, uint8_t base)
{
        static char res[16] = {0};
        static char res2[16] = {0};
        int i = 0;
        while (n > 0)
        {
                res[i] = n10[n % base];
                n /= base;
                i++;
        }
        for (int j = 0; j < i; j++)
        {
                res2[j] = res[i - j - 1];
        }
        return res2;
}
