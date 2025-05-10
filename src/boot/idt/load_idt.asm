bits 32

global load_idt

load_idt:
  push ebp
  mov ebp, esp
  
  mov edx,[esp + 4]
  lidt [edx]
  sti ; Turn interrupts on

  mov esp, ebp
  pop ebp
  ret
