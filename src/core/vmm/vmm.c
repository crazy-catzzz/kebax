// Virtual memory manager

#include "../../include/vmm.h"
#include "../../include/pmm.h"

#define PAGE_TABLE_SIZE 1024
#define PAGE_DIRECTORY_SIZE 1024

// ASM functions
extern void vmm_load_page_directory(page_directory_entry_t* page_directory);
extern void vmm_enable_paging();

// Topmost structure
/*page_directory_entry_t* page_directory;


// Flush TLB
void _flush_tlb_entry(uint32_t addr) {
  asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}


// Map address
void _map_addr(uint32_t phys_addr, uint32_t virt_addr, int flags) {
  page_table_entry_t* page_table;

  // Trim addresses
  phys_addr = phys_addr & 0xFFFFF000;
  virt_addr = virt_addr & 0xFFFFF000;

  // Calculate indexes
  int pd_index = (virt_addr >> 22) & 0x00000FFF;
  int pt_index = (virt_addr >> 12) & 0x00000FFF;

  // Check if page directory entry already exists
  if (!(page_directory[pd_index] & PAGE_PRESENT)) {
    page_table = pmm_alloc_frame();
  } else {
    page_table = (page_directory_entry_t*) (page_directory[pd_index] & 0xFFFFF000);
  }

  // Fill entries
  page_table[pt_index] = (page_table_entry_t) (phys_addr | flags);
  page_directory[pd_index] = (page_directory_entry_t) ((uintptr_t)page_table | (uintptr_t)flags);
}

// Identity mapping
void _id_page(uint32_t phys_addr, int flags) {
  _map_addr(phys_addr, phys_addr, flags);
}

// Get physical address from virtual address
void* vmm_virt_to_phys(uint32_t virt_addr) {
  // Calculate indexes
  int pd_index = (virt_addr >> 22) & 0x00000FFF;
  int pt_index = (virt_addr >> 12) & 0x00000FFF;

  // Use self referencing PDE trick to get physical address
  page_directory_entry_t* page_dir = (page_directory_entry_t*)0xFFFFF000;
  page_table_entry_t* page_table = ((page_table_entry_t*)0xFFC00000) + (0x400*pd_index);

  return (void*)((page_table[pt_index] & ~0xFFF) + (virt_addr & 0xFFF));
}

// Create Page Directory and enable paging
void vmm_init_paging() {
  page_directory = pmm_alloc_frame(); // Allocate frame for page directory

  // Fill page directory, top level
  for (int i = 0; i < PAGE_DIRECTORY_SIZE; i++) {
    page_directory[i] = 0x00000000 | PAGE_RW;
  }

  // Identity map the first 2MB to idmap the page directory
  for (int i = 0; i < 512; i++) { 
    _id_page(0x0+i*0x1000, PAGE_RW | PAGE_PRESENT);
  }

  // Higher half kernel mapping
  for (int i = 0; i < 1024; i++) {
    _map_addr(0x100000+i*0x1000, 0xC0000000+i*0x1000, PAGE_RW | PAGE_PRESENT);
  }
  
  // Self referencing PDE trick
  page_directory[1023] = (page_directory_entry_t) ((uintptr_t)page_directory | (uintptr_t)(PAGE_RW | PAGE_PRESENT));

  vmm_load_page_directory(page_directory);
  vmm_enable_paging();
}*/
