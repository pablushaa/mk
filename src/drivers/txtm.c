#include "txtm.h"

void
txtm_init_txtm(void)
{
        ROW = 0;
        COL = 0;
        COLOR = 0x0F;
}

void
txtm_set_cur(uint8_t row, uint8_t col)
{
        ROW = row;
        COL = col;
}

void
txtm_set_col(uint8_t color)
{
        COLOR = color;
}

void
txtm_clear_scr(void)
{
        for (int i = 0; i < 80 * 25; i++)
        {
                vmem[i * 2] = 0;
                vmem[i * 2 + 1] = COLOR;
        }
}

/* print one char */
void
txtm_printkc(char c)
{
        if (ROW == 24)
        {
                for (int i = 160; i < 80 * 25 * 2; i++)
                {
                        vmem[i - 160] = vmem[i];
                }
                ROW--;
        }
        if (c == '\n') { ROW++; COL=0; return; }
        if (c == '\r') { COL=0; return; }
        uint16_t pos = (ROW * 80 + COL) * 2;
        vmem[pos] = c;
        vmem[pos + 1] = COLOR;
        COL++;
        if (COL % 80 == 0 && COL != 0)
        {
                COL = 0;
                ROW++;
        }
}

/* print string */
void
txtm_printks(char *s)
{
        while (*s) txtm_printkc(*s++);
}
