// Keyboard Driver, puts scancodes in a circular buffer

#include "../include/port.h"
#include "../include/keyboard.h"

#define KB_STATUS 0x64
#define KB_DATA 0x60

#define BUF_SIZE 128

// Circular keyboard buffer
char kb_buffer[BUF_SIZE];
int buf_head = 0;
int buf_tail = 0;

unsigned char scan_map[128] = {
  0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
  0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
  '\'', '`',   0,		/* Left shift */
  '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

// Interrupt Request callback
void kb_irq_callback() {
  write_port(0x20, 0x20); // Interrupt has been seen
  
  char scancode;
  unsigned char status;

  status = read_port(KB_STATUS);
  if (status & 0x01) {
    scancode = read_port(KB_DATA);
    
    char ch = kb_scan_to_char(scancode);
    if (ch == 0) return;  // Ignore special keys

    // Put character into buffer
    kb_buffer[buf_head] = ch;
    buf_head = (buf_head + 1) % BUF_SIZE;

    if (buf_head == buf_tail) {
      buf_tail = (buf_tail + 1) % BUF_SIZE;
    }
  }
}

// Scancode to character conversion
char kb_scan_to_char(char scancode) {
  return scan_map[scancode];
}

// stdin-like with read blocking
char kb_read_buffer() {
  while (buf_head == buf_tail);

  char c = kb_buffer[buf_tail];
  buf_tail = (buf_tail + 1) % BUF_SIZE;

  return c;
}

// Ignore all previous characters and only get the latest
char kb_get_next_char() {
  buf_head = buf_tail;  // Flush buffer
  
  char c = kb_read_buffer();
  return c;
}
