[EXTERN isr_handler]

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Lower 16-bits of eax = ds.
   push eax                 ; save the data segment descriptor

   mov ax, 0x10             ; load the kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call isr_handler

   pop eax        ; reload the original data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   popa           ; Pops edi,esi,ebp...
   add esp, 8     ; Cleans up the pushed error code and pushed ISR number
   sti
   iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP


; We don't get information about which interrupt was caller when the handler is run, so we will need to have a different handler for every interrupt.
; Some interrupts push error code onto stack but others don't, so we'll push dummy error code for those which don't, to have consistent stack for all of them.
; e.g. Here interrupts 8, 10-14 inclusive push error codes onto the stack. The rest require dummy error codes.

; Using macro we can cover for all 32 versions of isr & cut down repeating code
; define a macro, taking one parameter that will distinguish between isr that requires error code or not. 
; %1 accesses the first parameter. stub handler function can call with ISR_NOERRCODE 0 or ISR_NOERRCODE 1

%macro ISR_NOERRCODE 1
  [GLOBAL isr%1]        
  isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
  [GLOBAL isr%1]
  isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro