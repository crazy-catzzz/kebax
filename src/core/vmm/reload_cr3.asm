bits 32

global reload_cr3

reload_cr3:
  push ebp
  mov ebp, esp
  
  mov ebx, cr3
  mov cr3, ebx
  
  mov esp, ebp
  pop ebp
  ret
