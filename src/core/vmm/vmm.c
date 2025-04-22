// Virtual memory manager

#include "../../include/vmm.h"
#include "../../include/pmm.h"

#define PAGE_TABLE_SIZE 1024
#define PAGE_DIRECTORY_SIZE 1024

// ASM functions
extern void vmm_load_page_directory(page_directory_entry_t* page_directory);
extern void vmm_enable_paging();

// Topmost structure
page_directory_entry_t* page_directory;


// Create Page Table and Page Directory Entry
page_directory_entry_t vmm_create_page_table() {
  page_table_entry_t* page_table = pmm_alloc_frame(); // Allocate frame for page table

  // Fill page table, middle level
  for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
    uint32_t* frame = pmm_alloc_frame();
    page_table[i] = (page_table_entry_t) ((uintptr_t)frame | (uintptr_t)3); // Set property bits:
                                                                            // SUPERVISOR
                                                                            // RW
                                                                            // PRESENT
  }

  return (page_directory_entry_t) ((uintptr_t)page_table | (uintptr_t)3); // Set property bits:
                                                                          // SUPERVISOR
                                                                          // RW
                                                                          // PRESENT
}

// Identity mapping
page_directory_entry_t vmm_id_page(uint32_t* start, int size) {
  page_table_entry_t* page_table = pmm_alloc_frame(); // Allocate frame for page table

  start = (uint32_t*) ((uintptr_t)start & (uintptr_t)0xFFFFF000); // Trim address

  for (int i = 0; i < size; i++) {
    page_table[i] = (page_table_entry_t) (((uintptr_t)start+(uintptr_t)i*(uintptr_t)0x1000) | (uintptr_t)3); // Set property bits:
                                                                                                             // SUPERVISOR
                                                                                                             // RW
                                                                                                             // PRESENT
  }

  return (page_directory_entry_t) ((uintptr_t)page_table | (uintptr_t)3); // Set property bits:
                                                                          // SUPERVISOR
                                                                          // RW
                                                                          // PRESENT
}

// Create Page Directory and enable paging
void vmm_init_paging() {
  page_directory = pmm_alloc_frame(); // Allocate frame for page directory

  // Fill page directory, top level
  for (int i = 0; i < PAGE_DIRECTORY_SIZE; i++) {
    page_directory[i] = 0x00000002; // Set property bits:
                                    // RW
  }
  
  page_directory[0] = vmm_id_page(0, 1024);  // Identity map the first 4MB

  vmm_load_page_directory(page_directory);
  vmm_enable_paging();
}
