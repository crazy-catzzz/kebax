bits 32

global kb_irq_handler
extern kb_irq_callback

kb_irq_handler:
  pusha ; Save registers
  call kb_irq_callback
  popa  ; Restore registers
  iretd
