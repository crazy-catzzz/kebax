#include "../include/basic_vga.h"
#include "../include/keyboard.h"
#include "../include/idt.h"
#include <stdbool.h>

int kern_main() {
  vga_init_color(COLORSCHEME_BLACKGREY);
  vga_clear_screen();
  puts("Kebax v0.0.1-alpha-scarraFOSS\n");

  puts("Control successfully handed over to C kernel!\n");

  puts("Initializing Interrupt Descriptor Table...\n");
  idt_init();
  puts("Done!\n");

  puts("Enabling IRQ1...\n");
  idt_enable_interrupt(1);
  puts("Done!\n");

  putc(kb_get_next_char());

  while(true);
}
