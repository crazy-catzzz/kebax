bits 32

global stage2
extern _main

extern gdt_init
extern idt_init
extern pic_init
extern unmap_useless

stage2:
  cli ; Clear interrupts
  mov esp, stack_space ; Init stack

  call unmap_useless
  ;call gdt_init
  call pic_init ; Maybe will replace with APIC/IOAPIC
  call idt_init

  call _main ; Hand control over to C kernel entrypoint
  hlt

; Init stack space
section .bss
resb 8192 ; 8KB stack space
stack_space: ; Stack goes from bottom to top
