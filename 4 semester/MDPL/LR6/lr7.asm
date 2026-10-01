.model small
.stack 100h
.data
    a           dd  0.8
    b           dd  2.5
    dval        dd  1.2
    x           dd  0.5
    step        dd  0.3
    count       dw  8
    msgX        db 13,10,'X = $'
    msgY        db '    Y = $'
    newline     db 13,10,'$'
    scale       dd  10000.0
    temp        dd  ?
    temp2       dd  ?
    temp3       dd  ?
    temp4       dd  ?
    printbuf    dd  ?
    two         dd  2.0
    twentyfour  dd  24.0
    c720        dd  720.0

.code
start:
    mov ax, @data
    mov ds, ax
    finit
    mov cx, count

main_loop:
    ; ===== вычисляем cos(a*d) =====
    fld  a
    fmul dval
    fstp temp               ; temp = t

    fld  temp
    fmul temp
    fstp temp2              ; temp2 = t^2

    fld  temp2
    fmul temp2
    fstp temp3              ; temp3 = t^4

    fld  temp3
    fmul temp2
    fstp temp4              ; temp4 = t^6

    fld1
    fld  temp2
    fdiv two
    fsubp st(1), st(0)
    fld  temp3
    fdiv twentyfour
    faddp st(1), st(0)
    fld  temp4
    fdiv c720
    fsubp st(1), st(0)
    fstp temp               ; temp = cos(a*d)

    ; ===== числитель: sqrt(b^2 + d*cos(a*d)) =====
    fld  b
    fmul b
    fld  dval
    fmul temp
    faddp st(1), st(0)
    fsqrt
    fstp temp               ; temp = числитель

    ; ===== вычисляем cos(x) =====
    fld  x
    fmul x
    fstp temp2              ; temp2 = x^2

    fld  temp2
    fmul temp2
    fstp temp3              ; temp3 = x^4

    fld  temp3
    fmul temp2
    fstp temp4              ; temp4 = x^6

    fld1
    fld  temp2
    fdiv two
    fsubp st(1), st(0)
    fld  temp3
    fdiv twentyfour
    faddp st(1), st(0)
    fld  temp4
    fdiv c720
    fsubp st(1), st(0)

    ; ===== знаменатель: x * cos(x) =====
    fmul x
    fstp temp2              ; temp2 = знаменатель

    ; ===== Y = числитель / знаменатель =====
    fld  temp
    fdiv temp2
    fstp temp               ; temp = Y

    ; ===== вывод X =====
    mov  ah, 9
    lea  dx, msgX
    int  21h
    fld  x
    call PrintFixed

    ; ===== вывод Y =====
    mov  ah, 9
    lea  dx, msgY
    int  21h
    fld  temp
    call PrintFixed

    mov  ah, 9
    lea  dx, newline
    int  21h

    ; ===== x += step =====
    fld  x
    fadd step
    fstp x

    dec  cx
    jz   exit_loop
    jmp  main_loop

exit_loop:
    mov  ah, 4Ch
    int  21h

; ==========================================
PrintFixed proc
    push ax
    push bx
    push cx
    push dx

    fld  scale
    fmulp st(1), st(0)
    fistp dword ptr printbuf

    mov  ax, word ptr printbuf
    mov  dx, word ptr printbuf+2

    test dx, 8000h
    jnz  pf_negative
    jmp  pf_positive

pf_negative:
    push dx
    mov  dl, '-'
    mov  ah, 2
    int  21h
    pop  dx
    not  ax
    not  dx
    add  ax, 1
    adc  dx, 0
    jmp  pf_positive

pf_positive:
    mov  bx, 10000
    div  bx
    push dx
    call PrintNumber
    mov  dl, '.'
    mov  ah, 2
    int  21h
    pop  ax
    call PrintFraction4

    pop  dx
    pop  cx
    pop  bx
    pop  ax
    ret
PrintFixed endp

; ==========================================
PrintNumber proc
    push ax
    push bx
    push cx
    push dx

    mov  cx, 0
    mov  bx, 10
pn_convert:
    xor  dx, dx
    div  bx
    push dx
    inc  cx
    test ax, ax
    jnz  pn_convert

pn_print:
    pop  dx
    add  dl, '0'
    mov  ah, 2
    int  21h
    loop pn_print

    pop  dx
    pop  cx
    pop  bx
    pop  ax
    ret
PrintNumber endp

; ==========================================
PrintFraction4 proc
    push ax
    push bx
    push cx
    push dx

    mov  bx, 10
    mov  cx, 4
pf4_push:
    xor  dx, dx
    div  bx
    push dx
    loop pf4_push

    mov  cx, 4
pf4_print:
    pop  dx
    add  dl, '0'
    mov  ah, 2
    int  21h
    loop pf4_print

    pop  dx
    pop  cx
    pop  bx
    pop  ax
    ret
PrintFraction4 endp

end start