#include <stdio.h>
#include <math.h>

double f(double x, double y, double a, int nm1, int nm2);
double calc_first_sum(double x, int nm1);
double calc_second_sum(double x, double y, int nm2);
void tabulate(double x0, double xh, double xn, double y0, double yh, double yn, double a, int nm1, int nm2);

int main(void) {
    double x0, xh, xn;
    double y0, yh, yn;
    double a;
    int nm1, nm2;

    printf("=== Табулирование функции f(x, y) ===\n");
    
    do {
        printf("Введите диапазон x (x0, шаг, xn): ");
        scanf("%lf %lf %lf", &x0, &xh, &xn);
        if (x0 >= xn) {
            printf("Ошибка: x0 должен быть меньше xn\n");
        }
    } while (x0 >= xn);
    
    do {
        printf("Введите диапазон y (y0, шаг, yn): ");
        scanf("%lf %lf %lf", &y0, &yh, &yn);
        if (y0 >= yn) {
            printf("Ошибка: y0 должен быть меньше yn\n");
        }
    } while (y0 >= yn);

    printf("Введите параметр a: ");
    scanf("%lf", &a);

    do {
        printf("Введите nm1 (2-6): ");
        scanf("%d", &nm1);
        if (nm1 < 2 || nm1 > 6) {
            printf("Ошибка: nm1 должен быть в диапазоне [2, 6]\n");
        }
    } while (nm1 < 2 || nm1 > 6);

    do {
        printf("Введите nm2 (2-6): ");
        scanf("%d", &nm2);
        if (nm2 < 2 || nm2 > 6) {
            printf("Ошибка: nm2 должен быть в диапазоне [2, 6]\n");
        }
    } while (nm2 < 2 || nm2 > 6);

    printf("\nТаблица значений функции f(x, y):\n");
    printf("------------------------------------------------------------\n");
    printf("|     x     |     y     |          f(x, y)                 |\n");
    printf("------------------------------------------------------------\n");

    tabulate(x0, xh, xn, y0, yh, yn, a, nm1, nm2);

    printf("------------------------------------------------------------\n");

    return 0;
}

double calc_first_sum(double x, int nm1) {
    double sum = 0.0;
    for (int n = 1; n <= nm1; n++) {
        sum += pow(x, n) / (3.0 * n);
    }
    return sum;
}

double calc_second_sum(double x, double y, int nm2) {
    if (fabs(y) < 1e-12) {
        printf("Ошибка: знаменатель равен 0 (y = 0), функция не существует\n");
        return NAN; // Возвращаем NaN (Not a Number) для обозначения ошибки
    }
    
    double sum = 0.0;
    for (int n = 0; n <= nm2; n++) {
        double den = 2 * pow(y, n + 1) + x * n;
        if (fabs(den) < 1e-12) {
            printf("Ошибка: знаменатель равен 0, функция не существует\n");
            return NAN; // Возвращаем NaN при нулевом знаменателе
        }
        sum += (3 * x + y) / den;
    }
    return sum;
}

double f(double x, double y, double a, int nm1, int nm2) {
    if (x < a)
        return calc_first_sum(x, nm1);
    else
        return calc_second_sum(x, y, nm2);
}

void tabulate(double x0, double xh, double xn, double y0, double yh, double yn, double a, int nm1, int nm2) {
    double xmax = x0, ymax = y0, fmax = -1e9;
    double xmin = x0, ymin = y0, fmin = 1e9;
    int valid_values_found = 0;

    for (double x = x0; x <= xn; x += xh) {
        for (double y = y0; y <= yn; y += yh) {
            double val = f(x, y, a, nm1, nm2);
            
            if (isnan(val)) {
                printf("| %8.3lf | %8.3lf | %28s |\n", x, y, "ОШИБКА: функция не существует");
            } else {
                printf("| %8.3lf | %8.3lf | %28.6lf |\n", x, y, val);
                valid_values_found = 1;

                if (val > fmax) {
                    fmax = val;
                    xmax = x;
                    ymax = y;
                }
                if (val < fmin) {
                    fmin = val;
                    xmin = x;
                    ymin = y;
                }
            }
        }
    }

    if (valid_values_found) {
        printf("\nМаксимум функции: f(%.3lf, %.3lf) = %.6lf\n", xmax, ymax, fmax);
        printf("Минимум функции: f(%.3lf, %.3lf) = %.6lf\n", xmin, ymin, fmin);
    } else {
        printf("\nВнимание: не найдено ни одного допустимого значения функции\n");
    }
}
