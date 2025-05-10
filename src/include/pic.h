#pragma once

#define PIC1_COMMAND 0x20
#define PIC2_COMMAND 0xA0
#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1

void pic_init(void);
void pic_enable_interrupt(char interrupt_code);
