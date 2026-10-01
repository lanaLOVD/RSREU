.section __TEXT,__text
.global _main
.extern _system

_main:
    sub sp, sp, #16
    stp x29, x30, [sp]
    add x29, sp, #0

    adrp x0, msg1@PAGE
    add  x0, x0, msg1@PAGEOFF
    bl   _system

    adrp x0, msg2@PAGE
    add  x0, x0, msg2@PAGEOFF
    bl   _system

    ldp x29, x30, [sp]
    add sp, sp, #16
    mov x0, #0
    ret

.section __DATA,__data

msg1:
.asciz "osascript -e 'display dialog \"Введите знак зодиака\" buttons {\"Овен\",\"Телец\",\"Лев\"}'"

msg2:
.asciz "osascript -e 'display dialog \"Тебе подходит BMW M3\" buttons {\"OK\"}'"
