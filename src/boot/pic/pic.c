#include "../../include/port.h"
#include "../../include/pic.h"

// Function to enable an interrupt, gets the interupt mask and modifies it
void pic_enable_interrupt(char interrupt_code) {
  if (interrupt_code < 8) { // IRQ0 - IRQ7 are handled by PIC1
    unsigned char mask = read_port(PIC1_DATA);
    mask &= ~(1 << interrupt_code);
    write_port(PIC1_DATA, mask);
  } else {  // IRQ8 - IRQ15 are handled by PIC2
    unsigned char mask = read_port(PIC2_DATA);
    mask &= ~(1 << (interrupt_code - 8));
    write_port(PIC2_DATA, mask);
  }
}

void pic_init() {
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
}
