.section __TEXT,__text
.global _main
.extern _system

_main:
    sub sp, sp, #16
    stp x29, x30, [sp]
    add x29, sp, #0

    adrp x0, ask@PAGE
    add  x0, x0, ask@PAGEOFF
    bl   _system

    ldp x29, x30, [sp]
    add sp, sp, #16
    mov x0, #0
    ret

.section __DATA,__data

ask:
.asciz "osascript <<EOF\nset z to choose from list {\"Овен\",\"Телец\",\"Близнецы\",\"Рак\",\"Лев\",\"Дева\",\"Весы\",\"Скорпион\",\"Стрелец\",\"Козерог\",\"Водолей\",\"Рыбы\"} with title \"Натальная карта\" with prompt \"Выбери знак зодиака\"\nif z is false then return\nset s to item 1 of z\nif s is \"Овен\" then display dialog \"♈ Овен\\nТебе подходит: BMW M3\\nЛидер, скорость, драйв\" buttons {\"OK\"}\nif s is \"Телец\" then display dialog \"♉ Телец\\nТебе подходит: Mercedes E-Class\\nКомфорт и статус\" buttons {\"OK\"}\nif s is \"Близнецы\" then display dialog \"♊ Близнецы\\nТебе подходит: Mini Cooper\\nЛёгкость и стиль\" buttons {\"OK\"}\nif s is \"Рак\" then display dialog \"♋ Рак\\nТебе подходит: Volvo XC90\\nБезопасность и семья\" buttons {\"OK\"}\nif s is \"Лев\" then display dialog \"♌ Лев\\nТебе подходит: Porsche Cayenne\\nХаризма и роскошь\" buttons {\"OK\"}\nif s is \"Дева\" then display dialog \"♍ Дева\\nТебе подходит: Toyota Camry\\nПрактичность и порядок\" buttons {\"OK\"}\nif s is \"Весы\" then display dialog \"♎ Весы\\nТебе подходит: Audi A7\\nБаланс и красота\" buttons {\"OK\"}\nif s is \"Скорпион\" then display dialog \"♏ Скорпион\\nТебе подходит: Dodge Challenger\\nСила и характер\" buttons {\"OK\"}\nif s is \"Стрелец\" then display dialog \"♐ Стрелец\\nТебе подходит: Jeep Wrangler\\nСвобода и приключения\" buttons {\"OK\"}\nif s is \"Козерог\" then display dialog \"♑ Козерог\\nТебе подходит: Lexus RX\\nНадёжность и класс\" buttons {\"OK\"}\nif s is \"Водолей\" then display dialog \"♒ Водолей\\nТебе подходит: Tesla Model 3\\nБудущее и технологии\" buttons {\"OK\"}\nif s is \"Рыбы\" then display dialog \"♓ Рыбы\\nТебе подходит: Range Rover\\nМечтательность и комфорт\" buttons {\"OK\"}\nEOF"
