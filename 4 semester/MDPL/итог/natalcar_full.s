.section __TEXT,__text
.global _main
.extern _system

_main:
    sub sp, sp, #16
    stp x29, x30, [sp]
    add x29, sp, #0

    adrp x0, menu@PAGE
    add  x0, x0, menu@PAGEOFF
    bl   _system

    adrp x0, result@PAGE
    add  x0, x0, result@PAGEOFF
    bl   _system

    ldp x29, x30, [sp]
    add sp, sp, #16
    mov x0, #0
    ret

.section __DATA,__data

menu:
.asciz "osascript -e 'choose from list {\"Овен\",\"Телец\",\"Близнецы\",\"Рак\",\"Лев\",\"Дева\",\"Весы\",\"Скорпион\",\"Стрелец\",\"Козерог\",\"Водолей\",\"Рыбы\"} with title \"Натальная карта\" with prompt \"Выбери знак зодиака\"'"

result:
.asciz "osascript -e 'display dialog \"♈ Овен → BMW M3\n♉ Телец → Mercedes E-Class\n♊ Близнецы → Mini Cooper\n♋ Рак → Volvo XC90\n♌ Лев → Porsche Cayenne\n♍ Дева → Toyota Camry\n♎ Весы → Audi A7\n♏ Скорпион → Dodge Challenger\n♐ Стрелец → Jeep Wrangler\n♑ Козерог → Lexus RX\n♒ Водолей → Tesla Model 3\n♓ Рыбы → Range Rover\n\nВыбери свой знак в первом окне 😄\" buttons {\"OK\"} with icon note'"
