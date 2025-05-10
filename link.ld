OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

SECTIONS {
  . = 0x00100000;

  .multiboot : {
    out/boot.o(.text)
  }

  .stage1 : {
    out/stage1.o(*)
    out/init_paging.o(*)
  }

  . += 0xC0000000;
  .text ALIGN (4K) : AT (ADDR (.text) - 0xC0000000) { 
    *(.text) 
  }
  .data ALIGN (4K) : AT (ADDR (.data) - 0xC0000000) { 
    *(.data)
  }
  .rodata ALIGN (4K) : AT (ADDR (.rodata) - 0xC0000000) {
    *(.rodata)
  }
  .bss  ALIGN (4K) : AT (ADDR (.bss) - 0xC0000000) {
    *(.bss)
  }
  kern_end = ALIGN(4K);

  /DISCARD/ : {*(*)}
}
