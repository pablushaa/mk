#ifndef TXTM_H
#define TXTM_H

#include <stdint.h>

#define BG_BLACK 0x00
#define BG_BLUE  0x10
#define BG_GREEN 0x20
#define BG_CYAN  0x30
#define BG_RED   0x40
#define BG_MAG   0x50
#define BG_ORANG 0x60
#define BG_LGRAY 0x70

#define BG_DGRAY 0x80
#define BG_LBLUE 0x90
#define BG_LGREN 0xA0
#define BG_LCYAN 0xB0
#define BG_LRED  0xC0
#define BG_PINK  0xD0
#define BG_YELOW 0xE0
#define BG_WHITE 0xF0

#define FG_BLACK 0x00
#define FG_BLUE  0x01
#define FG_GREEN 0x02
#define FG_CYAN  0x03
#define FG_RED   0x04
#define FG_MAG   0x05
#define FG_BROWN 0x06
#define FG_LGRAY 0x07

#define FG_DGRAY 0x08
#define FG_LBLUE 0x09
#define FG_LGREN 0x0A
#define FG_LCYAN 0x0B
#define FG_LRED  0x0C
#define FG_PINK  0x0D
#define FG_YELOW 0x0E
#define FG_WHITE 0x0F

void txtm_init_txtm(void);
void txtm_set_cur(uint8_t row, uint8_t col);
void txtm_set_color(uint8_t color);
void txtm_clear_scr(void);
void txtm_printks(char* s);
void txtm_printkc(char c);

#endif
