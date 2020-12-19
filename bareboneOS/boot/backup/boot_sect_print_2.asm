[org 0x7c00]
mov ah, 0x0e
mov bx, message

print_loop:
    mov al, [bx]
    int 0x10
    cmp al, 0
    je end
    add bx, 1
    jmp print_loop

end:
    jmp $   ; infinite loop

message:
    db "Booting BareboneOS", 0

; zero padding and magic bios number
times 510-($-$$) db 0
dw 0xaa55