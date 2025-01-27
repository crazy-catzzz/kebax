#include "../../include/port.h"
#include "../../include/idt.h"

struct IDT_Entry IDT[IDT_SIZE];

void idt_fill_entry(int code, unsigned long handler) {
  unsigned long address;

  address = handler;
  IDT[code].offset_lowerbits = address & 0xFFFF;
  IDT[code].selector = KERNEL_CODE_SEGMENT_OFFSET;
  IDT[code].zero = 0;
  IDT[code].type_attribute = INTERRUPT_GATE;
  IDT[code].offset_higherbits = (address & 0xFFFF0000) >> 16;
}

void idt_init(void) {
  unsigned long idt_addr;
  unsigned long idt_ptr[2];

  // ICW1 Init
  write_port(PIC1_COMMAND, 0x11);
  write_port(PIC2_COMMAND, 0x11);

  // ICW2 Vector offset
  write_port(PIC1_DATA, 0x20);
  write_port(PIC2_DATA, 0x28);

  // ICW3 Cascading (OFF)
  write_port(PIC1_DATA, 0x00);
  write_port(PIC2_DATA, 0x00);

  // ICW4 Environment
  write_port(PIC1_DATA, 0x01);
  write_port(PIC2_DATA, 0x01);

  // Mask interrupts
  write_port(PIC1_DATA, 0xFF);
  write_port(PIC2_DATA, 0xFF);

  idt_addr = (unsigned long)IDT;
  idt_ptr[0] = (sizeof(struct IDT_Entry) * IDT_SIZE) + ((idt_addr & 0xFFFF) << 16);
  idt_ptr[1] = idt_addr >> 16;

  load_idt(idt_ptr);
}
