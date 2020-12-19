[bits 32]
[extern main]   ; Define calling point external symbol. Must have same name as kernel.c 'main', function so the linker can substitute the final address.
call main       ; Calls the C function. The linker will know where it is placed in memory.
jmp $