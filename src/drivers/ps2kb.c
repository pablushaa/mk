#include "ps2kb.h"

uint8_t shift_st = 0;

/* default scan codes */
static uint8_t sc_arr[128] = {
        0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
        0x08, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
        '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '\\',
        0, 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
        0, 0, 0,  ' ',
};

/* shift scan codes */
static uint8_t sc_arr_sh[128] = {
        0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-',
        0x08, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
        0, 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '|',
        0, 0, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
        0, 0, 0,  ' ',
};

/* keyboard interrupt */
void
ps2kb_intr(registers_t* regs)
{
        uint8_t scan = inb(0x60);
        if (scan & 0x80)
        {
                if (scan == 0xAA || scan == 0xB6) { shift_st = 0; }
        } /* release */
        else
        {
                if (scan == 0x36 || scan == 0x2A) { shift_st = 1; }
                else if (sc_arr[scan] && shift_st == 0) { txtm_printkc(sc_arr[scan]); }
                else if (sc_arr_sh[scan] && shift_st == 1) { txtm_printkc(sc_arr_sh[scan]); }
                /* else
                {
                        txtm_printks("key ");
                        txtm_printks(itoa(scan, 16));
                        txtm_printkc(' ');
                        txtm_printkc('\n');
                } */
        }
}
