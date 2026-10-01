; Лабораторная работа №6, вариант 6
; N = (a + c) * (b + c) / w + c + w
; Вычисление над целыми и действительными числами

.MODEL SMALL
.STACK 100h

.DATA
    ; Целые числа (word)
    a_w    DW  10       ; целое a
    b_w    DW  4        ; целое b
    c_w    DW  20       ; целое c
    f_w    DW  3        ; целое f (не используется в этом варианте)
    w_w    DW  2        ; целое w
    
    ; Действительные числа (double)
    a_d    DD  10.0     ; действительное a
    b_d    DD  4.0      ; действительное b
    c_d    DD  20.0     ; действительное c
    w_d    DD  2.0      ; действительное w
    
    ; Результаты
    N_w    DW  ?        ; целый результат
    N_d    DD  ?        ; действительный результат
    
    ; Строки для вывода
    msg_int    DB 'Integer result: $'
    msg_real   DB 'Real result: $'
    newline    DB 13,10,'$'
    
    ; Временные переменные
    temp1_w    DW  ?      ; временное хранение для целых
    temp2_w    DW  ?      ; временное хранение для целых
    temp1_d    DD  ?      ; временное хранение для действительных
    temp2_d    DD  ?      ; временное хранение для действительных

.CODE
START:
    mov ax, @DATA
    mov ds, ax
    
    ; ========================================
    ; Часть 1: Вычисление над целыми числами
    ; N = (a + c) * (b + c) / w + c + w
    ; ========================================
    
    finit                    ; инициализация FPU
    
    ; Вычисляем (a + c)
    fild    a_w              ; ST(0) = a
    fild    c_w              ; ST(0) = c, ST(1) = a
    fadd                    ; ST(0) = a + c
    fistp   temp1_w          ; сохраняем (a + c)
    
    ; Вычисляем (b + c)
    fild    b_w              ; ST(0) = b
    fild    c_w              ; ST(0) = c, ST(1) = b
    fadd                    ; ST(0) = b + c
    fistp   temp2_w          ; сохраняем (b + c)
    
    ; Умножаем (a + c) * (b + c)
    fild    temp1_w          ; ST(0) = (a + c)
    fild    temp2_w          ; ST(0) = (b + c), ST(1) = (a + c)
    fmul                    ; ST(0) = (a + c) * (b + c)
    
    ; Делим на w
    fild    w_w              ; ST(0) = w, ST(1) = (a+c)*(b+c)
    fdiv                    ; ST(0) = (a+c)*(b+c) / w
    
    ; Прибавляем c
    fild    c_w              ; ST(0) = c, ST(1) = результат деления
    fadd                    ; ST(0) = (a+c)*(b+c)/w + c
    
    ; Прибавляем w
    fild    w_w              ; ST(0) = w, ST(1) = предыдущий результат
    fadd                    ; ST(0) = (a+c)*(b+c)/w + c + w
    
    ; Сохраняем целый результат
    fistp   N_w              ; сохраняем в N_w
    
    ; ========================================
    ; Часть 2: Вычисление над действительными числами
    ; N = (a + c) * (b + c) / w + c + w
    ; ========================================
    
    finit                    ; очищаем FPU
    
    ; Вычисляем (a + c)
    fld     a_d              ; ST(0) = a
    fld     c_d              ; ST(0) = c, ST(1) = a
    fadd                    ; ST(0) = a + c
    fstp    temp1_d          ; сохраняем (a + c)
    
    ; Вычисляем (b + c)
    fld     b_d              ; ST(0) = b
    fld     c_d              ; ST(0) = c, ST(1) = b
    fadd                    ; ST(0) = b + c
    fstp    temp2_d          ; сохраняем (b + c)
    
    ; Умножаем (a + c) * (b + c)
    fld     temp1_d          ; ST(0) = (a + c)
    fld     temp2_d          ; ST(0) = (b + c), ST(1) = (a + c)
    fmul                    ; ST(0) = (a + c) * (b + c)
    
    ; Делим на w
    fld     w_d              ; ST(0) = w, ST(1) = (a+c)*(b+c)
    fdiv                    ; ST(0) = (a+c)*(b+c) / w
    
    ; Прибавляем c
    fld     c_d              ; ST(0) = c, ST(1) = результат деления
    fadd                    ; ST(0) = (a+c)*(b+c)/w + c
    
    ; Прибавляем w
    fld     w_d              ; ST(0) = w, ST(1) = предыдущий результат
    fadd                    ; ST(0) = (a+c)*(b+c)/w + c + w
    
    ; Сохраняем действительный результат
    fstp    N_d              ; сохраняем в N_d
    
    ; ========================================
    ; Вывод результатов
    ; ========================================
    
    ; Вывод целого результата
    mov     ah, 9
    lea     dx, msg_int
    int     21h
    
    mov     ax, N_w
    call    WriteInt
    
    mov     ah, 9
    lea     dx, newline
    int     21h
    
    ; Вывод действительного результата
    mov     ah, 9
    lea     dx, msg_real
    int     21h
    
    ; Преобразуем float в целое для вывода
    finit
    fld     N_d
    fistp   N_w
    
    mov     ax, N_w
    call    WriteInt
    
    ; Ожидание нажатия клавиши
    mov     ah, 0
    int     16h
    
    ; Выход в DOS
    mov     ax, 4C00h
    int     21h

; ========================================
; Процедура вывода целого числа (ax)
; ========================================
WriteInt proc
    push    ax
    push    bx
    push    cx
    push    dx
    
    mov     bx, 10
    xor     cx, cx
    
    cmp     ax, 0
    jge     @wi_positive
    neg     ax
    push    ax
    mov     ah, 2
    mov     dl, '-'
    int     21h
    pop     ax
    
@wi_positive:
    xor     dx, dx
    div     bx
    push    dx
    inc     cx
    cmp     ax, 0
    jne     @wi_positive
    
@wi_print:
    pop     dx
    add     dl, '0'
    mov     ah, 2
    int     21h
    loop    @wi_print
    
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    ret
WriteInt endp

END START
