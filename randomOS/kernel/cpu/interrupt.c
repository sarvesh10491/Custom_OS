#include "interrupt.h"
#include "../../drivers/screen.h"

/* To print the message which defines every exception */
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

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t r){
    kprint("received interrupt: ");
   //  char s[3];
   //  int_to_ascii(r.int_no, s);
   //  kprint(s);
   //  kprint("\n");
   //  kprint(exception_messages[r.int_no]);
   //  kprint("\n");
}