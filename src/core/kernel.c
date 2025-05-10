#include "../include/basic_vga.h"
#include <stdbool.h>

#include "../include/vmm.h"
#include <stdint.h>
#include "../include/pmm.h"
#include "../include/pic.h"

#include "../include/keyboard.h"

void panic(char* message) {
  vga_clear_screen();

  puts("PANIC! (at the disco)\n\n");
  
  puts("Error message: ");
  puts(message);

  while(true);
}

void _main() {
  vga_init_color(COLORSCHEME_BLACKGREY);
  vga_clear_screen();

  puts("Kebax v0.0.1-alpha-scarraFOSS\n");
  puts("Control successfully handed over to C kernel!\n");

  while(true);
}
