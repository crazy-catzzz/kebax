#pragma once
#include <stdint.h>

typedef uint32_t page_directory_entry_t;
typedef uint32_t page_table_entry_t;

#define PAGE_PRESENT 1
#define PAGE_RW 2
#define PAGE_USER 4

void vmm_init_paging();
void* vmm_virt_to_phys(uint32_t virt_addr);
