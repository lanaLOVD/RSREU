#include <stdio.h>

// Вспомогательная рекурсивная функция для Xk
double xk(int k) {
    double result;
    if (k == 0 || k == 1) {
        result = 1.0;
    } else {
        result = 0.7 * xk(k-1) + 1.1 * xk(k-2);
    }
    return result;
}

// Рекурсивная функция для суммы
double sum_rec(int N) {
    double total;
    if (N == 0) {
        total = 1.0;
    } else if (N == 1) {
        total = 2.0; // 1 + 1 = 2
    } else {
        total = sum_rec(N-1) + xk(N);
    }
    return total;
}

// Итеративная функция для суммы
double sum_iter(int N) {
    double total;
    if (N < 0) {
        total = 0;
    } else if (N == 0) {
        total = 1.0;
    } else if (N == 1) {
        total = 2.0;
    } else {
        double x0 = 1.0; // X0
        double x1 = 1.0; // X1
        total = x0 + x1; // сумма X0 + X1
        double x_current;
        
        for (int k = 2; k <= N; k++) {
            x_current = 0.7 * x1 + 1.1 * x0;
            total = total + x_current;
            
            // сдвигаем значения для следующей итерации
            x0 = x1;
            x1 = x_current;
        }
    }
    return total;
}

int main(void) {
    int N;
    double res_rec, res_iter;

    // Проверка ввода N
    do {
        printf("Введите N (>= 0): ");
        scanf("%d", &N);
        if (N < 0) {
            printf("Ошибка! N должно быть больше или равно 0.\n");
        }
    } while (N < 0);

    res_rec = sum_rec(N);
    res_iter = sum_iter(N);
    
    printf("Сумма (рекурсия): %.6f\n", res_rec);
    printf("Сумма (итерация): %.6f\n", res_iter);
    
    return 0;
}
