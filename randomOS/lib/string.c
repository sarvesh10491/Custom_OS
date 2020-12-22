#include "string.h"

void memory_set(void *dest, u8int val, u32int len){
    u8int *temp = (u8int *)dest;
    for ( ; len != 0; len--) 
        *temp++ = val;
}

