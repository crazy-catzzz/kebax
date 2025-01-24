#include "../include/basic_vga.h"
#include <stdbool.h>

int kern_main() {
  vga_init_color(COLORSCHEME_BLACKGREY);
  vga_clear_screen();
  puts("Kebax v0.0.1-alpha-scarraFOSS\n");

  puts("Control successfully handed over to C kernel!\n");

  while(true);
}
