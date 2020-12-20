// Initialises the GDT

#include "gdt.h"

// Lets us access our ASM functions from our C code.
extern void gdt_flush(u32int);

// Internal function prototypes.
static void __init_gdt();
static void __gdt_set_gate(s32int, u32int, u32int, u8int, u8int);

gdt_entry_t gdt_entries[5];     // 5 => code & data segment descriptor for kernel; code & data segment descriptors for user mode; and a null entry.
gdt_ptr_t   gdt_ptr;


void init_gdt(){
   // Initialise the global descriptor table.
   __init_gdt();
}


static void __init_gdt(){
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (u32int)&gdt_entries;

   __gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   __gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   __gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   __gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   __gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   gdt_flush((u32int)&gdt_ptr);
}


// Set the value of one GDT entry.
static void __gdt_set_gate(s32int num, u32int base, u32int limit, u8int access, u8int gran){
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
}