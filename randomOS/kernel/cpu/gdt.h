#ifndef GDT_H
#define GDT_H

#include "../../include/types.h"

// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change any of the alignment in the structure.
struct gdt_entry_struct{
   u16int limit_low;           // The lower 16 bits of the limit.
   u16int base_low;            // The lower 16 bits of the base.
   u8int  base_middle;         // The next 8 bits of the base.
   u8int  access;              // Access flags, determine what ring this segment can be used in.
   u8int  granularity;
   u8int  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;


// To tell processor where to find our GDT, we have to give it the address of special pointer structure
struct gdt_ptr_struct{
   u16int limit;               // The upper 16 bits of all selector limits.
   u32int base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;


// Initialisation function is publicly accessible.
void init_gdt();

#endif