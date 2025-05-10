#pragma once

#define IDT_SIZE 256
#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define INTERRUPT_GATE 0x8E

struct IDT_Entry {
  unsigned short int offset_lowerbits;
  unsigned short int selector;
  unsigned char zero;
  unsigned char type_attribute;
  unsigned short int offset_higherbits;
};

void idt_init(void);
