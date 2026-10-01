;;=================================================================
;;  ЗАДАНИЕ 11.3 — Использование цепочечных команд
;;  Источник: Абель П., Глава 11, с. 116
;;
;;  Условие задачи:
;;    DATASG SEGMENT PARA
;;      CONAME DB 'SPACE EXPLORERS INC.'   ; 20 байт — источник
;;      PRLINE DB 20 DUP(' ')              ; 20 байт — приёмник
;;    DATASG ENDS
;;
;;  Выполнить подпункты: а, б, в, г, д, е
;;=================================================================

STACKSG SEGMENT PARA STACK 'Stack'
        DW      32 DUP(?)
STACKSG ENDS

DATASG  SEGMENT PARA 'Data'
CONAME  DB      'SPACE EXPLORERS INC.'  ; Строка-источник, 20 байт
PRLINE  DB      20 DUP(' ')         ; Строка-приёмник, 20 пробелов
DATASG  ENDS

CODESG  SEGMENT PARA 'Code'
        ASSUME  CS:CODESG, DS:DATASG, SS:STACKSG, ES:DATASG

BEGIN   PROC    FAR                         ; Точка входа
        MOV     AX, DATASG
        MOV     DS, AX                       ; Инициализация DS
        MOV     ES, AX                       ; ES = DS (обязательно для цеп. команд!)
        MOV     SS, AX
        MOV     SP, 64

// а
// Пересылка CONAME → PRLINE слева направо (REP MOVSB, CLD)
        CLD                                  ; DF=0: обработка слева направо
        LEA     SI, CONAME                   ; SI → источник CONAME
        LEA     DI, PRLINE                   ; DI → приёмник PRLINE
        MOV     CX, 20                         ; Счётчик: 20 байт
        REP     MOVSB                        ; Переслать 20 байт из CONAME в PRLINE

// б
// Пересылка CONAME → PRLINE справа налево (REP MOVSB, STD)
        STD                                  ; DF=1: обработка справа налево
        LEA     SI, CONAME+19                ; SI → последний байт CONAME
        LEA     DI, PRLINE+19                ; DI → последний байт PRLINE
        MOV     CX, 20                         ; Счётчик: 20 байт
        REP     MOVSB                        ; Переслать 20 байт справа налево
        CLD                                  ; Восстановить DF=0 после STD

// в
// Загрузка 3-го и 4-го байтов CONAME в AX (LODSW)
        ;    CONAME: S(0) P(1) A(2) C(3) E(4)...
        ;    LODSW: AL = байт по SI, AH = байт по SI+1
        CLD                                  ; DF=0
        LEA     SI, CONAME+2                 ; SI → 3-й байт ('A', индекс 2)
        LODSW                                ; AL='A' (3-й), AH='C' (4-й)

// г
// Сохранение AX в PRLINE+5 (STOSW)
        ;--- г) Сохранение содержимого AX в PRLINE+5 -----------
        ;    AX после подпункта в): AL='A', AH='C'
        CLD                                  ; DF=0
        LEA     DI, PRLINE+5                 ; DI → PRLINE+5 (6-я позиция)
        STOSW                                ; Записать AX по адресу ES:DI

// д
// Сравнение CONAME и PRLINE — должны быть не равны (REPE CMPSB)
        CLD
        LEA     SI, CONAME                   ; DS:SI → CONAME
        LEA     DI, PRLINE                   ; ES:DI → PRLINE
        MOV     CX, 20
        REPE    CMPSB                        ; Сравнивать, пока байты равны
        JNE     NOT_EQUAL                    ; ZF=0 → нашли различие → ОК
        ;  Если дошли сюда — строки равны (ошибка логики)
NOT_EQUAL: 

// е
// Сканирование PRLINE на пробел, адрес символа → BH (REPNE SCASB)
        CLD
        LEA     DI, PRLINE                   ; ES:DI → начало PRLINE
        MOV     AL, ' '                        ; Искомый символ — пробел (20h)
        MOV     CX, 20                         ; Длина области поиска
        REPNE   SCASB                        ; Сканировать, пока AL ≠ [DI]
        JNZ     NO_SPACE                    ; ZF=0 → пробел не найден
        DEC     DI                             ; DI после SCASB указывает на след. байт
        MOV     BH, [DI]                    ; Переслать найденный символ в BH
NO_SPACE: 

        ;--- Завершение программы --------------------------------
        MOV     AX, 4C00H
        INT     21H                            ; Выход в DOS

BEGIN   ENDP
CODESG  ENDS
        END     BEGIN