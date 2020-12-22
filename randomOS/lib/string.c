#include "string.h"

void memory_set(u8int *dest, u8int val, u32int len){
    u8int *temp = (u8int *)dest;
    for ( ; len != 0; len--) 
        *temp++ = val;
}

