OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

SECTIONS {
  . = 0x00100000;
  .text : { *(.text) }
  .data ALIGN (0x1000) : { *(.data) }
  .bss  : {
    *(.bss)
    kern_end = .;
  }
}
