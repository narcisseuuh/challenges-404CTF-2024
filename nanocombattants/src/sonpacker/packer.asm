section .text
    global _start

_start:
    int3
    test rdx, rdx
    jle end
    mov rdx, rdx
    mov rax, 0
    jmp mainloop

mainloop:
    movzx ecx, byte [rsi + rax]
    xor byte [rdi + rax], cl
    add rax, 1
    cmp rax, rdx
    jnz mainloop

end:
    int3