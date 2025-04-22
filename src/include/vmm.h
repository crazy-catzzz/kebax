#pragma once
#include <stdint.h>

typedef uint32_t page_directory_entry_t;
typedef uint32_t page_table_entry_t;

void vmm_init_paging();
