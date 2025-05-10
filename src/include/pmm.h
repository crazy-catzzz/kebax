#pragma once
#include <stdint.h>

typedef void* frame_t;

frame_t pmm_alloc_frame();
void pmm_free_frame(frame_t frame);
