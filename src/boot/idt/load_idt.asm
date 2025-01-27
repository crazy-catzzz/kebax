bits 32

global load_idt

load_idt:
  mov edx,[esp + 4]
  lidt [esp]
  sti ; Turn interrupts on
  ret
