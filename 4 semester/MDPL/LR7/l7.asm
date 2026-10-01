.386
.model flat, stdcall
option casemap:none

include C:\masm32\include\windows.inc
include C:\masm32\include\kernel32.inc
include C:\masm32\include\user32.inc
include C:\masm32\include\fpu.inc

includelib C:\masm32\lib\kernel32.lib
includelib C:\masm32\lib\user32.lib
includelib C:\masm32\lib\fpu.lib

BSIZE equ 60

.data
    ; === Коэффициенты (можно менять) ===
    a   dd  0.8      ; коэффициент a
    b   dd  2.5      ; коэффициент b
    d   dd  1.2      ; коэффициент d

    x_start dd 0.5   ; начальное значение X
    step    dd 0.3   ; шаг
    count   dd 10    ; количество значений для вычисления

    ; Для вывода
    fmt     db "X = %.3f    Y = %.6f", 13, 10, 0
    buf     db BSIZE dup(?)
    stdout  dd ?
    cWritten dd ?

    ; Временные переменные для хранения X и Y
    tempX   dq ?
    tempY   dq ?

.code
start:
    invoke GetStdHandle, STD_OUTPUT_HANDLE
    mov stdout, eax

    fld x_start                  ; ST(0) = X
    mov ecx, count

calc_loop:
    ; Сохраняем текущее X
    fst qword ptr tempX

    ; === Вычисление Y с использованием FPU ===

    ; 1. Вычисляем числитель: sqrt( b² + d * cos(a * d) )
    fld d                        ; загрузить d
    fmul a                       ; a * d
    fcos                         ; cos(a * d)
    fmul d                       ; d * cos(a*d)

    fld b
    fmul b                       ; b²
    fadd                         ; b² + d*cos(a*d)

    fsqrt                        ; sqrt(...)

    ; 2. Вычисляем знаменатель: x * cos(x)
    fld qword ptr tempX          ; загрузить X
    fcos                         ; cos(X)
    fmul qword ptr tempX         ; X * cos(X)

    ; 3. Деление: Y = числитель / знаменатель
    fdiv                         ; ST(0) = Y

    fst qword ptr tempY          ; сохраняем Y

    ; === Вывод результата ===
    invoke FpuFLtoA, ADDR tempX, 3, ADDR buf, SRC1_REAL or SRC2_DIMM
    ; FpuFLtoA портит буфер, поэтому используем wsprintf для красивого вывода

    ; Более надёжный вывод через wsprintf
    push dword ptr [tempY+4]
    push dword ptr [tempY]
    push dword ptr [tempX+4]
    push dword ptr [tempX]
    push offset fmt
    push offset buf
    call wsprintf
    add esp, 24

    invoke WriteConsoleA, stdout, ADDR buf, eax, ADDR cWritten, NULL

    ; Следующее значение X = X + step
    fld qword ptr tempX
    fadd step
    dec ecx
    jnz calc_loop

    invoke ExitProcess, 0
end start