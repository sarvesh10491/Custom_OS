[org 0x7c00]

mov bx, first_message
call print
call print_nl

mov bp, 0x9000          ; set the stack safely away from current address
mov sp, bp

mov bx, MSG_REAL_MODE
call print
call print_nl


call switch_to_pm


; We can hang now
jmp $

; subroutines include below the hang
%include "boot_print_string.asm"
%include "boot_print_32.asm"
%include "boot_gdt_32.asm"
%include "boot_sect_switch_32.asm"


[bits 32]
BEGIN_PM:                       ; after the switch we will get here
    mov ebx, MSG_PROT_MODE
    call print_string_pm        ; Note that this will be written at the top left corner
    jmp $



; data
first_message:
    db 'Booting BareboneOS..', 0

MSG_REAL_MODE:
    db "Started in 16-bit real mode", 0

MSG_PROT_MODE:
    db "Loaded 32-bit protected mode", 0



; bootsector
; padding and magic number
times 510-($-$$) db 0
dw 0xaa55