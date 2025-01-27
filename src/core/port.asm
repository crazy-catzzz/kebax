bits 32

global write_port
global read_port

read_port:
  mov edx,[esp + 4]
  in al,dx
  ret

write_port:
  mov edx,[esp + 4]
  mov al,[esp + 4 + 4]
  out dx,al
  ret
