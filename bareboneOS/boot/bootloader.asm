; A boot sector that boots a C kernel in 32 - bit protected mode
[org 0x7c00]
KERNEL_OFFSET equ 0x1000    ; The same one we used when linking the kernel


mov bx, first_message
call print
call print_nl

mov [BOOT_DRIVE], dl    ; Remember that the BIOS sets us the boot drive in 'dl' on boot
mov bp, 0x9000          ; set the stack safely away from current address
mov sp, bp

mov bx, MSG_REAL_MODE
call print
call print_nl


call load_kernel        ; read & load the kernel from disk
call switch_to_pm       ; disable interrupts, load GDT etc. Finally jumps to 'BEGIN_PM'. Switch to protected mode from which we will not return.

jmp $                   ; Never executed

; ##########################
; subroutines included

%include "boot/boot_print_string.asm"
%include "boot/boot_print_hex.asm"
%include "boot/boot_print_32.asm"
%include "boot/boot_gdt_32.asm"
%include "boot/boot_sect_switch_32.asm"
%include "boot/boot_disk_load.asm"

; ##########################

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL     ; Print a message to say we are loading the kernel
    call print
    call print_nl

    mov bx, KERNEL_OFFSET       ; Setup parameters for our disk_load routine. Read from disk and store in 0x1000
    mov dh, 2                   ; load first 2 sectors (excluding boot sector) from boot disk (i.e. kernel code) to address KERNEL_OFFSET
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret


[bits 32]
BEGIN_PM:                       ; after the switch we will get here
    mov ebx, MSG_PROT_MODE
    call print_string_pm        ; Note that this will be written at the top left corner
    call KERNEL_OFFSET          ; Give control to the kernel
    jmp $                       ; Stay here when the kernel returns control to us (if ever)


; ##########################
; data
BOOT_DRIVE:
    db 0        ; It is a good idea to store it in memory because 'dl' may get overwritten

first_message:
    db 'Booting BareboneOS..', 0

MSG_REAL_MODE:
    db "Started in 16-bit real mode", 0

MSG_PROT_MODE:
    db "Loaded 32-bit protected mode", 0

MSG_LOAD_KERNEL: 
    db "Loading kernel into memory", 0

; ##########################

; bootsector padding
; padding and magic number
times 510-($-$$) db 0
dw 0xaa55