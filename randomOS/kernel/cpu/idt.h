#ifndef IDT_H
#define IDT_H

#include "../../include/types.h"
#include "../../include/port.h"
#include "../../lib/string.h"

// A struct describing an interrupt gate.
struct idt_entry_struct
{
   u16int base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   u16int sel;                 // Kernel segment selector.
   u8int  always0;             // This must always be zero.
   u8int  flags;               // More flags :
                               /*   * Bit 7: "Interrupt is present"
                                    * Bits 6-5: Privilege level of caller (0=kernel..3=user)
                                    * Bit 4: Set to 0 for interrupt gates
                                    * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
   u16int base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;


// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
   u16int limit;
   u32int base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;


/* ISRs reserved for CPU exceptions */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/* IRQ definitions */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

// Initialisation function is publicly accessible.
void init_idt();

#endif

/* The special, CPU-dedicated interrupts are shown below.

      0 - Division by zero exception
      1 - Debug exception
      2 - Non maskable interrupt
      3 - Breakpoint exception
      4 - 'Into detected overflow'
      5 - Out of bounds exception
      6 - Invalid opcode exception
      7 - No coprocessor exception
      8 - Double fault (pushes an error code)
      9 - Coprocessor segment overrun
      10 - Bad TSS (pushes an error code)
      11 - Segment not present (pushes an error code)
      12 - Stack fault (pushes an error code)
      13 - General protection fault (pushes an error code)
      14 - Page fault (pushes an error code)
      15 - Unknown interrupt exception
      16 - Coprocessor fault
      17 - Alignment check exception
      18 - Machine check exception
      19-31 - Reserved
*/