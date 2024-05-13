section .text
    global _start

_start:
    int3 ; 0
    nop

; ['0', 37, 231, 11] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0xb
    cmp rax, 0x3b

    int3 ; 1
    nop

; ['n', 209, 191, 188] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    add rax, 0x91
    cmp rax, 0xff

    int3 ; 2
    nop

; ['m', 195, 195, 184] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0x7f
    cmp rax, 0x12

    int3 ; 3
    nop

; ['4', 39, 93, 131] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0x83
    cmp rax, 0xb7

    int3 ; 4
    nop

; ['o', 30, 14, 41] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0x1e
    add rax, 0xe
    cmp rax, 0x7f

    int3 ; 5
    nop

; ['c', 49, 10, 17] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0x11
    cmp rax, 0x72

    int3 ; 6
    nop

    int3 ; 7
    nop