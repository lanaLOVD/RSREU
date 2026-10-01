; ============================================================
; ЛАБОРАТОРНАЯ РАБОТА №8 — Вариант 17 (нормальная версия)
; ============================================================

.MODEL SMALL
.386
.387
.STACK 200h

PRINT MACRO str_addr
    mov dx, OFFSET str_addr
    mov ah, 09h
    int 21h
ENDM

.DATA
    coef_a       DQ 1.5
    coef_b       DQ 2.0
    coef_d       DQ 0.5
    x_start      DQ 1.23
    x_end        DQ 8.57
    x_step       DQ 0.0
    N            EQU 10

    arr          DQ N DUP(0.0)
    cur_x        DQ 0.0

    tmp_int      DW 0
    tmp_frac     DW 0
    fpu_status   DW 0
    sign_flag    DB ' '

    msg_title    DB 'Variant 17: y = sqrt(b^2 + d*cos(a*d)) / (x*cos(x))',13,10,'$'
    msg_sep      DB '---------------------------------------------',13,10,'$'
    msg_col      DB '  i      X           Y',13,10,'$'
    msg_sort     DB 13,10,'Sorted (descending):',13,10,'$'
    msg_crlf     DB 13,10,'$'
    sp3          DB '   $'

    ten_thousand DQ 10000.0
    nine         DQ 9.0

.CODE

PrintUInt PROC NEAR
    push ax bx cx dx
    mov bx,10
    xor cx,cx
    test ax,ax
    jnz pu_div
    mov dl,'0'
    mov ah,02h
    int 21h
    jmp pu_done
pu_div:
    xor dx,dx
    div bx
    push dx
    inc cx
    test ax,ax
    jnz pu_div
pu_print:
    pop dx
    add dl,'0'
    mov ah,02h
    int 21h
    loop pu_print
pu_done:
    pop dx cx bx ax
    ret
PrintUInt ENDP

PrintFloat PROC NEAR
    push ax bx cx dx

    mov sign_flag, ' '
    fld st(0)
    ftst
    fstsw fpu_status
    fwait
    mov ax, fpu_status
    sahf
    jnc pf_pos
    mov sign_flag, '-'
    fchs
pf_pos:

    fld st(0)
    fistp tmp_int

    mov dl, sign_flag
    mov ah, 02h
    int 21h

    mov ax, tmp_int
    call PrintUInt

    mov dl, '.'
    mov ah, 02h
    int 21h

    fild tmp_int
    fsubp st(1), st
    fabs
    fmul ten_thousand
    frndint
    fistp tmp_frac

    mov ax, tmp_frac
    mov cx, 4
frac_loop:
    mov bx, 10
    xor dx, dx
    div bx
    push dx
    loop frac_loop

    mov cx, 4
print_frac:
    pop dx
    add dl, '0'
    mov ah, 02h
    int 21h
    loop print_frac

    pop dx cx bx ax
    ret
PrintFloat ENDP

main PROC FAR
    mov ax, @DATA
    mov ds, ax
    finit

    PRINT msg_title
    PRINT msg_sep
    PRINT msg_col
    PRINT msg_sep

    fld x_end
    fsub x_start
    fdiv nine
    fstp x_step

    fld x_start
    fstp cur_x

    xor si, si

calc_loop:
    cmp si, N
    jge calc_done

    fld coef_a
    fmul coef_d
    fcos
    fmul coef_d
    fld coef_b
    fmul coef_b
    fadd
    fsqrt

    fld cur_x
    fld st(0)
    fcos
    fmulp st(1), st
    fdiv

    mov bx, si
    shl bx, 3
    fstp arr[bx]

    fld cur_x
    fadd x_step
    fstp cur_x

    inc si
    jmp calc_loop

calc_done:

    ; ===== сортировка по УБЫВАНИЮ =====
    mov di, 0
outer:
    cmp di, N-1
    jge sort_done
    mov cx, N-1
    sub cx, di
    xor si, si

inner:
    cmp si, cx
    jge next_outer

    mov bx, si
    shl bx, 3

    fld arr[bx]        ; st0 = arr[i]
    fld arr[bx+8]      ; st0 = arr[i+1], st1 = arr[i]

    fcom st(1)         ; сравниваем arr[i+1] с arr[i]
    fstsw ax
    sahf

    fstp st(0)
    fstp st(0)

    jbe no_swap        ; если arr[i+1] >= arr[i] → не менять

    fld arr[bx]
    fld arr[bx+8]
    fstp arr[bx]
    fstp arr[bx+8]

no_swap:
    inc si
    jmp inner

next_outer:
    inc di
    jmp outer

sort_done:

    PRINT msg_sort
    PRINT msg_sep

    xor si, si

print_desc:
    cmp si, N
    jge finish

    mov dl, ' '
    mov ah, 02h
    int 21h
    mov ax, si
    call PrintUInt
    PRINT sp3

    mov bx, si
    shl bx, 3

    fld arr[bx]
    call PrintFloat
    PRINT msg_crlf

    inc si
    jmp print_desc

finish:
    mov ax, 4C00h
    int 21h

main ENDP
END main
