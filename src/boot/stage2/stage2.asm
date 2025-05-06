bits 32

; I'm already in 32-Bit protected mode since I'm using GRUB as my bootloader

global stage2
extern _main

stage2:
  cli ; Clear interrupts
  mov esp, stack_space ; Init stack
  ;push eax  ; GRUB memory map (?)
  ;push ebx  ; GRUB memory map (?)
  call _main ; Hand control over to C kernel entrypoint
  hlt

; Init stack space
section .bss
resb 8192 ; 8KB stack space
stack_space: ; Stack goes from bottom to top
