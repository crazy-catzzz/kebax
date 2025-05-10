#include <stdint.h>

void _unmap(uint32_t virt_addr) {
  uint32_t* page_directory = (uint32_t*) 0xFFFFF000;
  uint32_t* page_table;

  virt_addr = virt_addr & 0xFFFFF000;

  int pd_index = (virt_addr >> 22);
  int pt_index = (virt_addr >> 12) & 0x000003FF;

  if (!(page_directory[pd_index] & 1) || !(page_table[pt_index] & 1)) {
    return;
  }

  page_table[pt_index] = 0x00000000 | 2;  // Set properties:
                                          // RW

  reload_cr3();
}

void unmap_useless() {
  for (int i = 0; i < 1024; i++) {
    _unmap(0x0+i*0x1000); // Remove the 4MB identity mapping
  }
}
