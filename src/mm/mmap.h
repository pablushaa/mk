#ifndef MMAP_H
#define MMAP_H

#include <stdint.h>

#include "../util/convert.h"
#include "../drivers/txtm.h"
#include "../sys/types.h"
#include "../../config.h"

void mmap_init(void);
uint32_t mmap_gfree_pages(void);
void mmap_set_used(uint32_t addr, uint32_t len);
void mmap_set_free(uint32_t addr, uint32_t len);
uint32_t mmap_alloc_frame(void);

#endif
