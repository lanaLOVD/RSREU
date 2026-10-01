.section __DATA, __data
msg:    .ascii "Hello, World!\n"
len = . - msg

.section __TEXT, __text
.global _main

_main:
    mov x0, #1
    adrp x1, msg@PAGE
    add  x1, x1, msg@PAGEOFF
    mov x2, len
    mov x16, #4
    svc #0

    mov x0, #0
    mov x16, #1
    svc #0
