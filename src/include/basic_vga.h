#pragma once

#define COLORSCHEME_BLACKGREY 0x07

void putc(char c);
void puts(char* s);
void puti(int i);
void putx(unsigned long int x);

void vga_init_color(char color);
void vga_clear_screen(void);
