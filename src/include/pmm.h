#pragma once
#include <stdint.h>

typedef uint32_t* frame_t;

frame_t pmm_alloc_frame();
void pmm_free_frame();
void pmm_align_memory();
