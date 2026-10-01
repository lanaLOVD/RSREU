.section __TEXT, __text
.global _main
.extern _printf

_main:
    sub  sp, sp, #32
    stp  x29, x30, [sp, #16]
    add  x29, sp, #16

    ldr  d0, num1
    ldr  d1, num2
    fadd d0, d0, d1

    str  d0, [sp]

    adrp x0, fmt@PAGE
    add  x0, x0, fmt@PAGEOFF
    ldr  d0, [sp]
    bl   _printf

    ldp  x29, x30, [sp, #16]
    add  sp, sp, #32
    mov  x0, #0
    ret

.align 3
num1: .quad 0x4046c7ae147ae148
num2: .quad 0x403e2147ae147ae1

.section __DATA, __data
fmt: .asciz "Result: %.2f\n"
