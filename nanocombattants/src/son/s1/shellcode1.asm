section .text
    global _start

_start:
    int3 ; 0
    nop

; ['f', 247, 67, 4] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0x4
    cmp rax, 0x62

    int3 ; 1
    nop

; ['r', 92, 236, 173] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0x5c
    add rax, 0x4b
    cmp al, 0x79

    int3 ; 2
    nop

; ['_', 242, 29, 197] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    add rax, 0x1d
    cmp rax, 0x7c

    int3 ; 3
    nop

; ['3', 25, 12, 199] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    xor rax, 0xc7
    cmp rax, 0xf4

    int3 ; 4
    nop

; ['i', 83, 98, 161] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    add rax, 0x53
    cmp al, 0xbc

    int3 ; 5
    nop

; ['n', 151, 35, 135] offset done
    xor rax, rax
    mov al, byte [rdi]
    inc rdi
    add rax, 0x23
    xor rax, 0x87
    cmp rax, 0x16

    int3 ; 6
    nop

    int3 ; 7
    nop