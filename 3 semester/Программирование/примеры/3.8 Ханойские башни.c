#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Структура для хранения состояния задачи
typedef struct {
    int n;
    char src, aux, dest;
} HanoiState;

// Рекурсивная функция для решения задачи о Ханойских башнях
void hanoi_recursive(int n, char src, char aux, char dest) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", src, dest);
        return;
    }
    hanoi_recursive(n - 1, src, dest, aux);
    printf("Move disk %d from %c to %c\n", n, src, dest);
    hanoi_recursive(n - 1, aux, src, dest);
}

// Итеративная функция для решения задачи о Ханойских башнях
void hanoi_iterative(int n, char src, char aux, char dest) {
    HanoiState stack[1000];
    int top = -1;

    stack[++top] = (HanoiState) { n, src, aux, dest };

    while (top >= 0) {
        HanoiState curr = stack[top--];
        if (curr.n == 1) {
            printf("Move disk 1 from %c to %c\n", curr.src, curr.dest);
            continue;
        }
        stack[++top] = (HanoiState) { curr.n - 1, curr.aux, curr.src, curr.dest };
        printf("Move disk %d from %c to %c\n", curr.n, curr.src, curr.dest);
        stack[++top] = (HanoiState) { curr.n - 1, curr.src, curr.dest, curr.aux };
    }
}

// Функция для измерения времени выполнения
void measure_performance(void (*func)(int, char, char, char), int n, char src, char aux, char dest) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    func(n, src, aux, dest);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
}

int main() {
    int n = 10; // Количество дисков
    char src = 'A', aux = 'B', dest = 'C';

    printf("Recursive Hanoi:\n");
    measure_performance(hanoi_recursive, n, src, aux, dest);

    printf("\nIterative Hanoi:\n");
    measure_performance(hanoi_iterative, n, src, aux, dest);

    return 0;
}

