// Virtual memory manager

#include "../../include/vmm.h"
#include "../../include/pmm.h"

#define PAGE_TABLE_SIZE 1024
#define PAGE_DIRECTORY_SIZE 1024

// ASM functions
extern void reload_cr3();

// Map address
void _map_addr(uint32_t phys_addr, uint32_t virt_addr, int flags) {
  page_table_entry_t* page_table;
  page_directory_entry_t* page_directory = (page_directory_entry_t*) 0xFFFFF000;

  // Trim addresses
  phys_addr = phys_addr & 0xFFFFF000;
  virt_addr = virt_addr & 0xFFFFF000;

  // Calculate indexes
  int pd_index = (virt_addr >> 22);
  int pt_index = (virt_addr >> 12) & 0x000003FF;

  // Check if page directory entry already exists
  if (!(page_directory[pd_index] & PAGE_PRESENT)) {
    page_table = pmm_alloc_frame(); // Borked, PMM broke after higher half mapping
    page_directory[pd_index] = (page_directory_entry_t) ((uintptr_t)vmm_virt_to_phys(page_table) | (uintptr_t)flags); // UNTESTED
  } else {
    page_table = (page_directory_entry_t*) (pd_index << 22 | pd_index << 12);
  }

  // Fill entries
  page_table[pt_index] = (page_table_entry_t) (phys_addr | flags);
  page_directory[pd_index] = (page_directory_entry_t) ((uintptr_t)page_table | (uintptr_t)flags);

  reload_cr3();
}

// Get physical address from virtual address
void* vmm_virt_to_phys(uint32_t virt_addr) {
  page_directory_entry_t* page_directory = (page_directory_entry_t*) 0xFFFFF000;
  page_table_entry_t* page_table;

  // Calculate indexes
  int pd_index = (virt_addr >> 22) & 0x00000FFF;
  int pt_index = (virt_addr >> 12) & 0x000003FF;

  page_table = (page_table_entry_t*) (pd_index << 22 | pd_index << 12);

  return (void*)((page_table[pt_index] & ~0xFFF) + (virt_addr & 0xFFF));
}
