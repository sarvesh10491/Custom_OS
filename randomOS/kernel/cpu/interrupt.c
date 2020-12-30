#include "interrupt.h"

/* To print the message which defines every exception */
// extern char *exception_messages[];
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

// This gets called from our ASM interrupt handler stub for ISR.
void isr_handler(registers_t r){
   kprint("Received interrupt : #");
   char s[3];
   int_to_ascii(r.int_no, s);
   kprint(s);
   kprint("  [");
   kprint(exception_messages[r.int_no]);
   kprint("]\n");
}


// This gets called from our ASM interrupt handler stub for IRQ.
void irq_handler(registers_t r){
   // After every interrupt we need to send an EOI to the PICs or they will not send another interrupt again
   if(r.int_no >= 40) 
      port_byte_out(0xA0, 0x20);    // slave
   port_byte_out(0x20, 0x20);       // master

   // Handle the interrupt in a more modular way. Select registered handler from list & call it.
   if(interrupt_handlers[r.int_no] != 0){
      isr_t handler = interrupt_handlers[r.int_no];
      handler(r);
   }
}


void register_interrupt_handler(u8int n, isr_t handler){
   interrupt_handlers[n] = handler;
}