; N = c – (a + b – w) * f / (a + w)
; Вычисление над целыми и действительными числами

.MODEL SMALL
.STACK 100h

.DATA
    ; Целые числа (word)
    a_w    DW  10       ; целое a
    b_w    DW  4        ; целое b
    c_w    DW  20       ; целое c
    f_w    DW  3        ; целое f
    w_w    DW  2        ; целое w
    
    ; Действительные числа (double)
    a_d    DD  10.0     ; действительное a
    b_d    DD  4.0      ; действительное b
    c_d    DD  20.0     ; действительное c
    f_d    DD  3.0      ; действительное f
    w_d    DD  2.0      ; действительное w
    
    ; Результаты
    N_w    DW  ?        ; целый результат
    N_d    DD  ?        ; действительный результат
    
    ; Строки для вывода
    msg_int    DB 'Integer result: $'
    msg_real   DB 'Real result: $'
    newline    DB 13,10,'$'
    
    ; Временные переменные
    temp_denom_w   DW  ?      ; для целых
    temp_denom_d   DD  ?      ; для действительных

.CODE
START:
    mov ax, @DATA
    mov ds, ax
    
    ; Вычисление над целыми числами
    ; N = c – (a + b – w) * f / (a + w)
    
    finit                    ; инициализация FPU
    
    ; Вычисляем знаменатель (a + w)
    fild    a_w              ; ST(0) = a
    fild    w_w              ; ST(0) = w, ST(1) = a
    fadd                    ; ST(0) = a + w
    fistp   temp_denom_w     ; сохраняем знаменатель
    
    ; Вычисляем (a + b – w)
    fild    a_w              ; ST(0) = a
    fild    b_w              ; ST(0) = b, ST(1) = a
    fadd                    ; ST(0) = a + b
    fild    w_w              ; ST(0) = w, ST(1) = a + b
    fsub                    ; ST(0) = (a + b) - w
    
    ; Умножаем на f
    fild    f_w              ; ST(0) = f, ST(1) = (a+b-w)
    fmul                    ; ST(0) = (a+b-w) * f
    
    ; Делим на (a + w)
    fild    temp_denom_w     ; ST(0) = (a+w), ST(1) = (a+b-w)*f
    fdiv                    ; ST(0) = (a+b-w)*f / (a+w)
    
    ; Вычисляем c - (результат)
    fild    c_w              ; ST(0) = c, ST(1) = результат деления
    fsub    st, st(1)        ; ST(0) = c - (результат деления)
    
    ; Сохраняем целый результат
    fistp   N_w              ; сохраняем в N_w, стек очищается
    
    ; Часть 2: Вычисление над действительными числами
    ; N = c – (a + b – w) * f / (a + w)
    
    finit                    ; очищаем FPU
    
    ; Вычисляем знаменатель (a + w)
    fld     a_d              ; ST(0) = a
    fld     w_d              ; ST(0) = w, ST(1) = a
    fadd                    ; ST(0) = a + w
    fstp    temp_denom_d     ; сохраняем знаменатель
    
    ; Вычисляем (a + b – w)
    fld     a_d              ; ST(0) = a
    fld     b_d              ; ST(0) = b, ST(1) = a
    fadd                    ; ST(0) = a + b
    fld     w_d              ; ST(0) = w, ST(1) = a + b
    fsub                    ; ST(0) = (a + b) - w
    
    ; Умножаем на f
    fld     f_d              ; ST(0) = f, ST(1) = (a+b-w)
    fmul                    ; ST(0) = (a+b-w) * f
    
    ; Делим на (a + w)
    fld     temp_denom_d     ; ST(0) = (a+w), ST(1) = (a+b-w)*f
    fdiv                    ; ST(0) = (a+b-w)*f / (a+w)
    
    ; Вычисляем c - (результат)
    fld     c_d              ; ST(0) = c, ST(1) = результат деления
    fsub    st, st(1)        ; ST(0) = c - результат деления
    
    ; Сохраняем действительный результат
    fstp    N_d              ; сохраняем в N_d
    
    ; Вывод результатов
    
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
    
    ; Преобразуем float в целое для простого вывода
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

; Процедура вывода целого числа (ax)
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