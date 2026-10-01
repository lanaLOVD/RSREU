#include <stdio.h>
#include <locale.h>



int main(void) {
    setlocale(LC_ALL, "Russian");
    
    int A, B, C;
    int Z_asm = 0;     // Результат операции
    int isPrime = 1;   // Флаг простоты

    printf("Введите значения переменных:\n");
    printf("A = "); scanf("%d", &A);
    printf("B = "); scanf("%d", &B);
    printf("C = "); scanf("%d", &C);

    // -- Основной расчет в ассемблере --
    asm (
        "movl %[A], %%eax;\n\t"       // EAX = A
        "cltd;\n\t"                   // Расширение знакового разряда
        "idivl %[B];\n\t"             // EAX = A / B
        "addl %[C], %%eax;\n\t"      // EAX = (A / B) + C
                "movl %%eax, %[Z];\n\t"      // Z = результат деления

        "cmpl $0, %%eax;\n\t"         // Сравниваем Z и 0
        "jl less_than_zero;\n\t"      // Переход, если Z меньше нуля
        "jmp check_prime;\n\t"        // Иначе идём проверять простоту

        "less_than_zero:\n\t"
            "movl %[A], %%eax;\n\t"   // EAX = A
            "movl %[C], %%ebx;\n\t"   // EBX = C
            "cltd;\n\t"
            "movl %[AB_sum], %%ecx;\n\t" // ECX = A + B
            "idivl %%ecx;\n\t"        // EAX = C/(A+B)
            "subl %%eax, %[A];\n\t"  // AX = A - C/(A+B)
            "movl %%eax, %[Z];\n\t"  // Новый Z = A - C/(A+B)
        "check_prime:\n\t"
            "cmp $2, %[Z];\n\t"
            "jb not_prime;\n\t"
            "movl $2, %%ecx;\n\t"
            "movl %[Z], %%eax;\n\t"
            "cltd;\n\t"
            "div_loop:\n\t"
                "xorl %%edx, %%edx;\n\t"
                "idivl %%ecx;\n\t"
                "testl %%edx, %%edx;\n\t"
                "jz not_prime;\n\t"
                "incl %%ecx;\n\t"
                "cmpl %%ecx, %[Z];\n\t"
                "jg prime_found;\n\t"
                "jmp div_loop;\n\t"
                
        "prime_found:\n\t"
            "movl $1, %[isPrime];\n\t" // Это простое число
            "jmp end_check;\n\t"

        "not_prime:\n\t"
            "movl $0, %[isPrime];\n\t" // Число составное
            
        "end_check:"
        : [Z]"=r"(Z_asm), [isPrime]"=r"(isPrime)
        : [A]"r"(A), [B]"r"(B), [C]"r"(C), [AB_sum]"r"(A + B)
        : "%eax", "%ebx", "%ecx", "%edx"
    );

    // Вывод итогового результата
    if (Z_asm < 0) {
        printf("\nТак как Z < 0 → новое Z = %d\n", Z_asm);
    } else {
        if (isPrime)
            printf("\nZ = %d — простое число\n", Z_asm);
        else
            printf("\nZ = %d — не простое число\n", Z_asm);
    }

    return 0;
}
