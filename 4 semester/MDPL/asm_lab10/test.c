#include <stdio.h>
int main() {
    double a = 45.56;
    double b = 30.13;
    printf("%.2f + %.2f = %.2f\n", a, b, a+b);
    
    // покажем hex представление
    unsigned long *pa = (unsigned long*)&a;
    unsigned long *pb = (unsigned long*)&b;
    printf("num1 hex: 0x%016lx\n", *pa);
    printf("num2 hex: 0x%016lx\n", *pb);
    return 0;
}
