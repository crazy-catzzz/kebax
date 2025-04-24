#include "../include/basic_vga.h"
#include "../include/keyboard.h"
#include "../include/idt.h"
#include "../include/vmm.h"
#include "../include/pmm.h"
#include "../include/gnu_multiboot.h"
#include <stdbool.h>

void panic(char* message) {
  vga_clear_screen();

  puts("PANIC! (at the disco)\n\n");
  
  puts("Error message: ");
  puts(message);

  while(true);
}

void _main(multiboot_info_t* mbd, unsigned int magic) {
  vga_init_color(COLORSCHEME_BLACKGREY);
  vga_clear_screen();

  // MEMORY DETECTION
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    panic("Invalid bootloader magic number!");
  }

  if (!(mbd->flags >> 6 & 0x1)) {
    panic("Invalid memory map!");
  }

  for (int i = 0; i < mbd->mmap_length; i+=sizeof(multiboot_memory_map_t)) {
    multiboot_memory_map_t* map = (multiboot_memory_map_t*) (mbd->mmap_addr + i);

    puts("Start addr: ");
    putx(map->addr);

    puts(" | Length: ");
    putx(map->len);

    puts(" | Size: ");
    putx(map->size);

    puts(" | Type: ");
    puti(map->type);

    putc('\n');

    if (map->type == MULTIBOOT_MEMORY_AVAILABLE) {

    }
  }
  putc('\n');

  kern_main();
}

int kern_main() {
  pmm_align_memory();
  vmm_init_paging();

  puts("Kebax v0.0.1-alpha-scarraFOSS\n");
  puts("Control successfully handed over to C kernel!\n");
  
  idt_init();
  idt_enable_interrupt(1);
  
  while(true);
}
