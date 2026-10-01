from math import *

n = int(input('Введите начальное значение суммы: '))
if n > 0:
    N = int(input('Введите конечное значение суммы: '))
    if N > 0 and N >= n:
        print(f'n = {n}    N = {N}')
        S = 0
        for x in range(n, N + 1):
            u = tan(2 * x) + cos(3 * x) + sin(4 * x)**5 - 22 * tan(7 * x)
            S = S + u
        print(f'Значение суммы равно {S}')
    else:
        print('Значение не удовлетворяет условию')
else:
    print('Значение не удовлетворяет условиям')