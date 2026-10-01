.section __TEXT, __text
.global _main
.extern _printf
.extern _cos

_main:
    sub  sp, sp, #32
    stp  x29, x30, [sp, #16]
    add  x29, sp, #16

    // загружаем x, a, b, c, d
    ldr  d0, val_x       // d0 = x = 2.0
    ldr  d1, val_x
    fmul d0, d0, d1      // d0 = x*x = 4.0

    ldr  d1, val_a       // d1 = a = 1.0
    fadd d0, d0, d1      // d0 = x^2 + a = 5.0

    // cos(x^2 + a)
    bl   _cos            // d0 = cos(5.0)

    str  d0, [sp]        // сохраняем числитель

    // знаменатель: b*c + d^2
    ldr  d1, val_b
    ldr  d2, val_c
    fmul d1, d1, d2      // d1 = b*c = 12.0

    ldr  d2, val_d
    ldr  d3, val_d
    fmul d2, d2, d3      // d2 = d^2 = 4.0

    fadd d1, d1, d2      // d1 = b*c + d^2 = 16.0

    ldr  d0, [sp]        // восстанавливаем числитель
    fdiv d0, d0, d1      // d0 = результат

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
val_x: .double 2.0
val_a: .double 1.0
val_b: .double 3.0
val_c: .double 4.0
val_d: .double 2.0

.section __DATA, __data
fmt: .asciz "y = %.6f\n"
