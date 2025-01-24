#include "../include/basic_vga.h"

#define SCR_COLS 80
#define SCR_ROWS 25
#define CELL_SIZE 2

volatile char* video_mem = (volatile char*)0xB8000;

// Theoretical screen coordinates
int lineno = 0;
int colno = 0;

// Actual index in video memory
int mem_index = 0;

// Init color
char* video_color;
void vga_init_color(char color) {
  video_color = color;
}

// Clear screen
void vga_clear_screen(void) {
    int i = 0;
    while (i < SCR_COLS * SCR_ROWS * CELL_SIZE) {
        video_mem[i] = ' ';

        video_mem[i + 1] = video_color;

        i += CELL_SIZE;
    }
    lineno = 0;
}

// Send character to screen
void putc(char c) {
  if (c == 0) return;
  
  // Move to correct location in memory
  mem_index = colno + (SCR_COLS * lineno * CELL_SIZE);
  
  // Handle special characters
  switch (c) {
    case '\n':  // Newline
      lineno++;
      colno = 0;
      return;
      break;
    case '\b':  // Backspace
      colno -= CELL_SIZE;
      mem_index = colno + (SCR_COLS * lineno * CELL_SIZE);
      video_mem[mem_index] = ' ';
      return;
      break;
  }

  video_mem[mem_index] = c;
  video_mem[mem_index + 1] = video_color;

  colno += CELL_SIZE;
}

// Send string to screen
void puts(char* s) {
  // Strings end at \0
  for (int i = 0; s[i] != 0; i++) {
    putc(s[i]);
  }
}
