bits 32

global vmm_load_page_directory
global vmm_enable_paging

vmm_load_page_directory:
  push ebp
  mov ebp, esp
  mov eax, [esp + 8]
  mov cr3, eax  ; Move first argument (page directory address) in CR3
  mov esp, ebp
  pop ebp
  ret

vmm_enable_paging:
  push ebp
  mov ebp, esp
  mov eax, cr0  ; Make a copy of CR0
  mov ebx, 0x80000000 ; 0x8000000 is 10000000000000000000000000000000, an OR sets the 32nd bit to 1
  or eax, ebx
  mov cr0, eax  ; Store edited register value in CR0
  mov esp, ebp
  pop ebp
  ret
