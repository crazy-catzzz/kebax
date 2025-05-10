#include <stdint.h>

// Paging structures defined in stage1.asm
extern *page_directory;
extern *id_map_table;
extern *hh_map_table;

// Map address
void _map(uint32_t phys_addr, uint32_t virt_addr, int flags, uint32_t* page_table) {

  phys_addr = phys_addr & 0xFFFFF000;
  virt_addr = virt_addr & 0xFFFFF000;

  int pd_index = (virt_addr >> 22) & 0x000003FF;
  int pt_index = (virt_addr >> 12) & 0x000003FF;

  page_table[pt_index] = (uint32_t) (phys_addr | flags);
  page_directory[pd_index] = (uint32_t) ((uintptr_t)page_table | (uintptr_t)flags);
}

// Identity mapping
void _idp(uint32_t phys_addr, int flags, uint32_t* page_table) {
  _map(phys_addr, phys_addr, flags, page_table);
}

void init_paging() {
  for (int i = 0; i < 1024; i++) {
    _idp(0x0+i*0x1000, 3, id_map_table);  // Temporary identity mapping of the first 4MB
    _map(0x0+i*0x1000, 0xC0000000+i*0x1000, 3, hh_map_table); // Higher half kernel mapping
  }

  // Self referencing PDE to map while paging is active
  page_directory[1023] = (uint32_t) ((uintptr_t)page_directory | (uintptr_t)3);
}
