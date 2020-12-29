// interrupt.h -- Interface and structures for high level interrupt service routines.

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "../../include/types.h"
#include "../../include/port.h"
#include "../../drivers/screen.h"
#include "../../lib/string.h"

#define IRQ0    32
#define IRQ1    33
#define IRQ2    34
#define IRQ3    35
#define IRQ4    36
#define IRQ5    37
#define IRQ6    38
#define IRQ7    39
#define IRQ8    40
#define IRQ9    41
#define IRQ10   42
#define IRQ11   43
#define IRQ12   44
#define IRQ13   45
#define IRQ14   46
#define IRQ15   47

typedef struct registers
{
   u32int ds;                                      // Data segment selector
   u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;  // Pushed by pusha.
   u32int int_no, err_code;                        // Interrupt number and error code (if applicable)
   u32int eip, cs, eflags, useresp, ss;            // Pushed by the processor automatically.
} registers_t;

// Enables registration of callbacks for interrupts or IRQs.
// For IRQs, to ease confusion, use the "#defines IRQn" above as the first parameter.
typedef void (*isr_t)(registers_t);
void register_interrupt_handler(u8int n, isr_t handler);

isr_t interrupt_handlers[256];

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