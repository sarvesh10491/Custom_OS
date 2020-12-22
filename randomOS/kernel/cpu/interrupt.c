#include "interrupt.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t r){
   kprint("Received interrupt : #");
   char s[3];
   int_to_ascii(r.int_no, s);
   kprint(s);
   kprint("  [");
   kprint(exception_messages[r.int_no]);
   kprint("]\n");
}