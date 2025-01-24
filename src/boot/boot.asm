bits 32

; I'm already in 32-Bit protected mode since I'm using GRUB as my bootloader

; Multiboot spec
section .text
  align 4
  dd 0x1BADB002 ; Magic value
  dd 0x00
  dd - (0x1BADB002 + 0x00)

global start
extern kern_main

start:
  cli ; Clear interrupts
  mov esp, stack_space ; Init stack
  call kern_main ; Hand control over to C kernel entrypoint
  hlt

; Init stack space
section .bss
resb 8192 ; 8KB stack space
stack_space: ; Stack goes from bottom to top
