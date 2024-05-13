section .text
    global _start

_start:
    int3 ; 0
    nop

; ['t', 173, 153, 234] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0xea
    cmp rax, 0x9e

    int3 ; 1
    nop

; ['a', 104, 121, 187] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    add rax, 0x68
    xor rax, 0x79
    cmp rax, 0xb0

    int3 ; 2
    nop

; ['n', 163, 255, 7] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0x7
    cmp rax, 0x69

    int3 ; 3
    nop

; ['4', 22, 57, 212] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    add rax, 0x39
    cmp rax, 0x6d

    int3 ; 4
    nop

; ['b', 108, 59, 52] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0x6c
    cmp rax, 0xe

    int3 ; 5
    nop

; ['t', 208, 197, 51] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0x33
    cmp rax, 0x47

    int3 ; 6
    nop

; ['t', 110, 67, 25]
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    add rax, 0x43
    cmp rax, 0xb7

    int3 ; 7
    nop