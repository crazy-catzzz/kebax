bits 32

; I'm already in 32-Bit protected mode since I'm using GRUB as my bootloader

; Multiboot spec
section .text
  align 4
  dd 0x1BADB002 ; Magic value
  dd 0x00
  dd - (0x1BADB002 + 0x00)

global start
extern stage1

start:
  jmp stage1
