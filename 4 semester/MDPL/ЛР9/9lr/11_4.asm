;;=================================================================
;;  ЗАДАНИЕ 11.4 — Переделка процедуры H10SCAS
;;  Источник: Абель П., Глава 11, с. 116
;;
;;  Условие задачи:
;;    Переделать H10SCAS (рис.11.1) для поиска символа "er"
;;    в поле NAME1 = 'Assemblers' (10 байт).
;;    Проблема: "er" не выровнено по словам — /As/se/mb/le/rs/
;;    Два варианта решения: а) SCASW дважды, б) SCASB + CMP
;;=================================================================

STACKSG SEGMENT PARA STACK 'Stack'
        DW      32 DUP(?)
STACKSG ENDS

DATASG  SEGMENT PARA 'Data'
NAME1   DB      'Assemblers'          ; 10 байт-источник из рис.11.1
NAME2   DB      10 DUP(' ')       ; буфер
NAME3   DB      10 DUP(' ')       ; буфер
DATASG  ENDS

CODESG  SEGMENT PARA 'Code'
        ASSUME  CS:CODESG, DS:DATASG, SS:STACKSG, ES:DATASG

BEGIN   PROC    FAR
        MOV     AX, DATASG
        MOV     DS, AX                       ; Инициализация DS
        MOV     ES, AX                       ; ES = DS (для SCAS)
        CALL    H10SCAS_A                   ; Вызов варианта а)
        CALL    H10SCAS_B                   ; Вызов варианта б)
        MOV     AX, 4C00H
        INT     21H                            ; Выход в DOS
BEGIN   ENDP

;Вариант а) — SCASW дважды: чётные позиции (NAME1), затем нечётные (NAME1+1)
        ;--- а) Поиск "er" командой SCASW — два прохода ---------
        ;    SCASW сравнивает AX с словом [ES:DI].
        ;    Байты в слове: AL = младший (по адресу DI),
        ;                  AH = старший (по адресу DI+1).
        ;    Слово "er": AL='e'(65h), AH='r'(72h) → AX=7265h
H10SCAS_A PROC NEAR
        CLD                                  ; DF=0: слева направо

        ; Проход 1: начинаем с NAME1 (чётные позиции 0,2,4...)
        MOV     AX, 7265H                     ; AX: AL='e'(72h→нет!), см. ниже
        ;    Внимание: x86 little-endian — слово в памяти "er":
        ;    адрес N = 'e'(65h), адрес N+1 = 'r'(72h)
        ;    SCASW берёт: AL=[DI]='e', AH=[DI+1]='r'
        ;    Значит AX = ('r' << 8) | 'e' = 7265H
        MOV     AX, 7265H                     ; AX = "er" в порядке памяти
        MOV     CX, 5                          ; 5 слов = 10 байт (NAME1)
        LEA     DI, NAME1                    ; DI → начало NAME1
        REPNE   SCASW                        ; Искать слово "er" по чётным позициям
        JE      A_FOUND                     ; ZF=1 → найдено

        ; Проход 2: начинаем с NAME1+1 (нечётные позиции 1,3,5...)
        MOV     CX, 4                          ; 4 слова (9 байт с позиции 1)
        LEA     DI, NAME1+1                 ; DI → NAME1+1
        REPNE   SCASW                        ; Искать "er" по нечётным позициям
        JNE     A_NOT_FOUND                 ; ZF=0 → не найдено

A_FOUND:
        MOV     AH, 03H                      ; Признак: "er" найден
        JMP     A_EXIT
A_NOT_FOUND:
        MOV     AH, 00H                      ; Признак: не найдено
A_EXIT:
        RET
H10SCAS_A ENDP

;Вариант б) — SCASB ищет "e", затем CMP проверяет следующий байт на "r"
        ;--- б) Поиск "er": SCASB на 'e', затем CMP с 'r' --------
        ;    Надёжнее варианта а), т.к. не зависит от выравнивания.
        ;    После нахождения 'e' — DI указывает на следующий байт,
        ;    поэтому сравниваем [DI] с 'r' (без смещения -1).
H10SCAS_B PROC NEAR
        CLD                                  ; DF=0: слева направо
        MOV     CX, 10                         ; Длина NAME1 = 10 байт
        LEA     DI, NAME1                    ; ES:DI → начало NAME1
        MOV     AL, 'e'                        ; Искомый первый символ

B_SCAN: 
        REPNE   SCASB                        ; Искать 'e' в NAME1
        JCXZ    B_NOT_FOUND               ; CX=0 → 'e' не найден совсем
        CMP     BYTE PTR [DI], 'r'     ; Следующий байт = 'r'?
        JNE     B_SCAN                    ; Нет — продолжить поиск 'e'

        ; Если дошли сюда — найдена пара "er"
B_FOUND:
        MOV     AH, 03H                      ; Признак: "er" найден
        JMP     B_EXIT
B_NOT_FOUND:
        MOV     AH, 00H                      ; Признак: не найдено
B_EXIT:
        RET
H10SCAS_B ENDP

CODESG  ENDS
        END     BEGIN