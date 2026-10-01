.section __TEXT,__text
.global _main
.extern _system

_main:
    sub sp, sp, #16
    stp x29, x30, [sp]
    add x29, sp, #0

    adrp x0, cmd2@PAGE
    add  x0, x0, cmd2@PAGEOFF
    bl   _system

    ldp x29, x30, [sp]
    add sp, sp, #16
    mov x0, #0
    ret

.section __DATA,__data
cmd2:
.asciz "osascript -e 'display dialog \"Продолжить?\" buttons {\"OK\", \"Отмена\"}'"
