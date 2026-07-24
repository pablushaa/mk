#include "mmap.h"
#include "../../config.h"
#include "../drivers/txtm.h"
#include "../util/convert.h"
#include <stdint.h>

#define MMAP_CNT_ADDR 0x8FFE
#define MMAP_START    0x9000

static uint8_t mbitmap[MMAP_BITMAP_SIZE];
uint16_t* mmap_count = (uint16_t*) 0x8FFE;

/* initialise memory bitmap */
void
mmap_init(void)
{
        for (uint32_t i = 0; i < MMAP_BITMAP_SIZE; i++)
        {
                mbitmap[i] = 0xFF;
        }

        for (uint32_t i = MMAP_START; i < MMAP_START + *mmap_count * 24; i+=24)
        {
                e820_ent_t* ent = (e820_ent_t*) i;
                if (ent->type == 1) {
                        mmap_set_free(ent->addr_low, ent->len_low);
                } else {
                        mmap_set_used(ent->addr_low, ent->len_low);
                }
        }

        mmap_set_used(0, 0x100000); /* maybe i will remove this shit one day... but now it should be reserved just in case */
}

/* set some addresses as used */
void
mmap_set_used(uint32_t addr, uint32_t len)
{
        if (len == 0) return;

        uint32_t start = addr & ~0xFFF;
        uint64_t end_64 = ((uint64_t)addr + len + 0xFFF) & ~0xFFF;

        uint32_t start_frame = start >> 12;
        uint32_t max_frames = MMAP_BITMAP_SIZE * 8;
        uint64_t end_frame_64 = end_64 >> 12;

        if (end_frame_64 > max_frames) end_frame_64 = max_frames;
        if (end_frame_64 <= start_frame) return;

        uint32_t end_frame = (uint32_t)end_frame_64;

        for (uint32_t frame = start_frame; frame < end_frame; frame++) {
                mbitmap[frame >> 3] |= (1 << (frame & 7));
        }
}

/* set some addresses as free */
void
mmap_set_free(uint32_t addr, uint32_t len)
{
        if (len == 0) return;

        uint32_t start = addr & ~0xFFF;
        uint64_t end_64 = ((uint64_t)addr + len + 0xFFF) & ~0xFFF;

        uint32_t start_frame = start >> 12;
        uint32_t max_frames = MMAP_BITMAP_SIZE * 8;
        uint64_t end_frame_64 = end_64 >> 12;

        if (end_frame_64 > max_frames) end_frame_64 = max_frames;
        if (end_frame_64 <= start_frame) return;

        uint32_t end_frame = (uint32_t)end_frame_64;

        for (uint32_t frame = start_frame; frame < end_frame; frame++) {
                mbitmap[frame >> 3] &= ~(1 << (frame & 7));
        }
}

/* get free memory pages */
uint32_t
mmap_gfree_pages(void)
{
        uint32_t res = 0;
        for (uint32_t i = 0; i < MMAP_BITMAP_SIZE; i++)
        {
                for (uint8_t j = 0; j < 8; j++) {
                        if (((mbitmap[i] >> j) & 0x1)== 0)
                        {
                                res++;
                        }
                }
        }
        return res;
}

/* allocate one frame */
uint32_t
mmap_alloc_frame(void)
{
        for (uint32_t i = 0; i < MMAP_BITMAP_SIZE; i++)
        {
                for (uint8_t j = 0; j < 8; j++)
                {
                        if (((mbitmap[i] >> j) & 0x1) == 0)
                        {
                                uint32_t addr = ((i << 3) + j) * 4096;
                                mmap_set_used(addr, 4096);
                                return addr;
                        }
                }
        }
}
