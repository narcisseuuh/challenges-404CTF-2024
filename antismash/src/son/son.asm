section .text
    global _start

_start:
    ; precheck
    mov rax, qword [rsp]
    mov rbx, 0
    push rbp
    mov rbp, rsp
    push rsi
    push rdi
    int3

    ; Executes the routine
    jmp routine
; rdi = first param, rsi = second
routine:
    sub rsp, 0x20
    mov qword [rsp], 0
    mov qword [rsp + 8], 0
    mov qword [rsp + 0x10], 0
    mov qword [rsp + 0x18], 0

    mov rax, 1
    mov rdi, 1
    mov rsi, qword [rsp + 8 + 0x20]
    mov rdx, 71
    syscall ; syscall write halloeverynyan to stdout

    ; the options precised in creation.md
    ; routine read :
    nop ; to find these parts after xxd
    mov rax, 0
    mov rdi, 0
    mov rsi, rsp
    mov rdx, 0x100
    syscall ; syscall read to stdin of length 0x200
    int3

    ; routine write :
    int3
    nop
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 0x30
    syscall
    int3

    ; routine exit
    nop
    nop
    nop
    mov rax, 1
    mov rdi, 1
    mov rsi, qword [rsp + 0x20]
    mov rdx, 44
    syscall ; syscall write goodbye to stdout
    ; ending the routine
    jmp end

end:
    ; fixing potential overflow
    int3
    mov qword [rsp + 0x38], rax
    ; epilogue routine
    leave
    ret