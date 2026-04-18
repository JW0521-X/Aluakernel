[BITS 64]
SECTION .alua_header

SECTION .text
global _start
extern kernel_main

_start:

    cli

    mov rbp, rsp
    and rsp, -16
    sub rsp, 32
    
    mov rdi, rcx   
    call kernel_main

.halt:
    hlt
    jmp .halt

