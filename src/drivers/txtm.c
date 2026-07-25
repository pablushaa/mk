#include "txtm.h"

static char* vmem = (char*) 0xB8000;
static uint8_t ROW, COL, COLOR;

/* initialise text mode */
void
txtm_init_txtm(void)
{
        ROW = 0;
        COL = 0;
        COLOR = 0x0F;
}

/* set cursor at some position */
void
txtm_set_cur(uint8_t row, uint8_t col)
{
        ROW = row;
        COL = col;
}

void
txtm_set_color(uint8_t color)
{
        COLOR = color;
}

/* clear screen with COLOR */
void
txtm_clear_scr(void)
{
        for (int i = 0; i < 80 * 25; i++)
        {
                vmem[i * 2] = 0;
                vmem[i * 2 + 1] = COLOR;
        }
        ROW=0; COL=0;
}

/* print one char */
void
txtm_printkc(char c)
{
        uint8_t state = 1;
        /* scrolling */
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
        if (c == 0x08) /* backspace */
        {
                if (COL == 0 && ROW > 0) {ROW--; COL=79; }
                else {COL--;}
                c = ' ';
                state = 0;
        }

        uint16_t pos = (ROW * 80 + COL) * 2;
        vmem[pos] = c;
        vmem[pos + 1] = COLOR;

        COL += state;
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
        /* simple as hell! */
        while (*s) txtm_printkc(*s++);
}
