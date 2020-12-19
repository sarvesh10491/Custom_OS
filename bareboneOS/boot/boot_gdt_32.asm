gdt_start:
    ; the GDT starts with a null 8-byte
    dd 0x0 
    dd 0x0 

gdt_null : ; the mandatory null descriptor
    dd 0x0
    dd 0x0

; GDT for code segment. 
; base = 0x00000000, length = 0xfffff
; 1st flags : ( present )1 ( privilege )00 ( descriptor type )1 -> 1001 b
; type flags : ( code )1 ( conforming )0 ( readable )1 ( accessed )0 -> 1010 b
; 2nd flags : ( granularity )1 (32 - bit default )1 (64 - bit seg )0 ( AVL )0 -> 1100 b
gdt_code: 
    dw 0xffff       ; segment length, bits 0-15
    dw 0x0          ; segment base, bits 0-15
    db 0x0          ; segment base, bits 16-23
    db 10011010b    ; flags (8 bits)
    db 11001111b    ; flags (4 bits) + segment length, bits 16-19
    db 0x0          ; segment base, bits 24-31


; GDT for data segment. 
; base and length identical to code segment
; type flags : ( code )0 ( expand down )0 ( writable )1 ( accessed )0 -> 0010 b
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0


; The reason for putting label at end of GDT is so we can have assembler calculate size of GDT for GDT decriptor after
gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1      ; size (16 bit), always one less of its true size
    dd gdt_start                    ; address (32 bit)

; define some constants for later use
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start