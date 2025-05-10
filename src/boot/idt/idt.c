#include "../../include/port.h"
#include "../../include/idt.h"

struct IDT_Entry IDT[IDT_SIZE];

// IRQ Handlers declarations
extern void kb_irq_handler();

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

  // Add interrupts
  idt_fill_entry(0x21, (unsigned long)kb_irq_handler);  // Handler defined in src/core/irq

  idt_addr = (unsigned long)IDT;
  idt_ptr[0] = (sizeof(struct IDT_Entry) * IDT_SIZE) + ((idt_addr & 0xFFFF) << 16);
  idt_ptr[1] = idt_addr >> 16;

  load_idt(idt_ptr);
}
