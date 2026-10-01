.section __TEXT,__text
.global _main
.extern _system

// ================= MAIN =================
_main:
    sub sp, sp, #16
    stp x29, x30, [sp]
    add x29, sp, #0

// ====== зарплата ======
    adrp x0, askSalary@PAGE
    add  x0, x0, askSalary@PAGEOFF
    bl _system

// ====== цена ======
    adrp x0, askPrice@PAGE
    add  x0, x0, askPrice@PAGEOFF
    bl _system

// ====== знак ======
    adrp x0, zodiacMenu@PAGE
    add  x0, x0, zodiacMenu@PAGEOFF
    bl _system

// ====== универсальный результат ======
    adrp x0, baseMsg@PAGE
    add  x0, x0, baseMsg@PAGEOFF
    bl _system

// ====== подбор по знаку ======
    adrp x0, aries@PAGE
    add  x0, x0, aries@PAGEOFF
    bl _system

    adrp x0, taurus@PAGE
    add  x0, x0, taurus@PAGEOFF
    bl _system

    adrp x0, gemini@PAGE
    add  x0, x0, gemini@PAGEOFF
    bl _system

    adrp x0, bus@PAGE
    add  x0, x0, bus@PAGEOFF
    bl _system

// ====== итог ======
    adrp x0, result@PAGE
    add  x0, x0, result@PAGEOFF
    bl _system

    ldp x29, x30, [sp]
    add sp, sp, #16
    mov x0, #0
    ret


// ================= DATA =================
.section __DATA,__data

askSalary:
.asciz "osascript -e 'display dialog \"💰 Введи зарплату:\" default answer \"50000\" buttons {\"OK\"}'"

askPrice:
.asciz "osascript -e 'display dialog \"🚗 Введи цену машины:\" default answer \"3000000\" buttons {\"OK\"}'"

zodiacMenu:
.asciz "osascript -e 'choose from list {\"Овен\",\"Телец\",\"Близнецы\"} with prompt \"✨ Знак зодиака\"'"

// ---------- машины ----------
aries:
.asciz "osascript -e 'display dialog \"♈ Овен → BMW M3\" buttons {\"OK\"}'"

taurus:
.asciz "osascript -e 'display dialog \"♉ Телец → Mercedes S-Class\" buttons {\"OK\"}'"

gemini:
.asciz "osascript -e 'display dialog \"♊ Близнецы → Mini Cooper\" buttons {\"OK\"}'"

// ---------- автобус ----------
bus:
.asciz "osascript -e 'display dialog \"🚌 Слишком дорого → езди на автобусе\" buttons {\"OK\"}'"

// ---------- общий текст ----------
baseMsg:
.asciz "osascript -e 'display dialog \"📊 Считаем... если дорого — копи или бери кредит 😄\" buttons {\"OK\"}'"

result:
.asciz "osascript -e 'display dialog \"📈 Итог готов! Проверь выбранную машину\" buttons {\"OK\"}'"
