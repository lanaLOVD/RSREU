#include <iostream>
#include <cstdio>

int main() {
    int D, B, C, A, E, F, res, res1;

    printf("Input A, B, C, D, E, F values:\n");
    scanf("%d%d%d%d%d%d", &A, &B, &C, &D, &E, &F);

    // C++ версия
    res1 = D * (E + (A / C)) - F * ((B / F) + A);

    // ASM версия
    asm (
    // ---- вычисляем (A / C) ----
    "movl %[A], %%eax;"      // eax = A
    "cdq;"                   // расширяем знак в edx
    "idivl %[C];"            // eax = A / C
    "movl %%eax, %%ebx;"     // ebx = A/C

    // ---- вычисляем (E + A/C) ----
    "addl %[E], %%ebx;"      // ebx = E + (A/C)

    // ---- умножаем на D ----
    "imull %[D], %%ebx;"     // ebx = D * (E + A/C)

    // ---- вычисляем (B / F) ----
    "movl %[B], %%eax;"      // eax = B
    "cdq;"
    "idivl %[F];"            // eax = B / F

    // ---- (B/F + A) ----
    "addl %[A], %%eax;"      // eax = (B/F) + A

    // ---- умножаем на F ----
    "imull %[F], %%eax;"     // eax = F * (B/F + A)

    // ---- вычитаем ----
    "subl %%eax, %%ebx;"     // ebx = D*(E + A/C) - F*(B/F + A)

    "movl %%ebx, %[res];"    // res = ebx
    : [res] "=m" (res)
    : [A] "m" (A), [B] "m" (B), [C] "m" (C), [D] "m" (D), [E] "m" (E), [F] "m" (F)
    : "%eax", "%ebx", "%edx"
    );

    printf("Result (C++): %d * (%d + %d/%d) - %d * (%d/%d + %d) = %d\n", D, E, A, C, F, B, F, A, res1);

    printf("Result (asm): %d * (%d + %d/%d) - %d * (%d/%d + %d) = %d\n", D, E, A, C, F, B, F, A, res);

    return 0;
}
