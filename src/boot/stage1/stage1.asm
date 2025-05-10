bits 32

; Functions
global stage1
extern init_paging
extern stage2

; Paging structures
global page_directory
global id_map_table
global hh_map_table

; BOOT STAGE 1:
; - Get memory map
; - Fill page tables
; - Map kernel to higher half
; - Enable paging
; - Long jump to stage 2

; Page Directory and Page Tables
section .pages
  align 4096
  page_directory:
    resb 4096
  id_map_table:
    resb 4096
  hh_map_table:
    resb 4096

stage1:
  ; Filling the page tables is handled by C
  mov esp, tmp_stack

  ;push eax ; Args
  ;push ebx ; Args
  ;call get_mem_map

  call init_paging
  
  ; Load page directory
  mov eax, [page_directory]
  mov cr3, eax

  ; Enable paging
  mov eax, cr0
  or eax, 0x80000000
  mov cr0, eax

  ; Long jump to stage 2
  lea eax, [stage2]
  jmp eax

; Temporary stack, without it I wouldn't be able to call the init_paging() function
section .bss
    resb 4096
  tmp_stack:
