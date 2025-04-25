#pragma once
#include <stdint.h>

typedef uint32_t page_directory_entry_t;
typedef uint32_t page_table_entry_t;

#define PAGE_PRESENT 0x00000001
#define PAGE_RW 0x00000010
#define PAGE_USER 0x00000100

void vmm_init_paging();
void* vmm_virt_to_phys(uint32_t virt_addr);
