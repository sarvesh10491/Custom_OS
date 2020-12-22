// interrupt.h -- Interface and structures for high level interrupt service routines.

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "../../include/types.h"
#include "../../drivers/screen.h"
#include "../../lib/string.h"

typedef struct registers
{
   u32int ds;                                      // Data segment selector
   u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;  // Pushed by pusha.
   u32int int_no, err_code;                        // Interrupt number and error code (if applicable)
   u32int eip, cs, eflags, useresp, ss;            // Pushed by the processor automatically.
} registers_t;


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

#endif