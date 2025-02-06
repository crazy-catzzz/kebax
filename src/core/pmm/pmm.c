// Physical memory manager

#include "../../include/pmm.h"
#include <stdint.h>
#include <stddef.h>

#define FRAME_SIZE 4096
#define AVL_MEM_SIZE 0xFFFFFFFF - kern_end
#define BMP_SIZE AVL_MEM_SIZE / FRAME_SIZE
#define BMP_STATUS_USED 0x01
#define BMP_STATUS_FREE 0x00

// Available memory starting point
extern uint32_t kern_end;
frame_t frame_start = &kern_end;

// Memory frame bitmap
uint8_t* frame_map;

frame_t pmm_alloc_frame() {
  int found = -1;

  for (int i = 0; i < BMP_SIZE; i++) {
    if (frame_map[i] == BMP_STATUS_FREE) {
      frame_map[i] = BMP_STATUS_USED;
      found = i;

      break;
    }
  }

  // If no memory available
  if (found == -1) {
    return NULL;
  }

  // Return start address of frame
  return frame_start + (found*FRAME_SIZE);
}

void pmm_free_frame(frame_t frame) {
  // Calculate index from frame start address
  int index = (frame - frame_start)/FRAME_SIZE;

  frame_map[index] = BMP_STATUS_FREE;
}
