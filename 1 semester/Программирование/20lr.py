from math import *

def F(x):
    i = 4 * x ** 3 + x - 1
    return i

def F_derivative(x):  # Производная функции F(x)
    g = 12 * x ** 2 + 1
    return g

def NewtonMethod(a, b, eps):
    x = (a + b) / 2  # Начальное приближение
    k = 1
    while abs(F(x)) >= eps:
        derivative = F_derivative(x)
        if derivative == 0:
            print("Производная равна нулю. Метод Ньютона не применим.")
            return
        else:
            x = x - F(x) / derivative
            k += 1
    print(f"Метод Ньютона: x = {x}, число итераций = {k}")

def ChordMethod(a, b, eps):
    x_prev = a
    x = b
    k = 1
    while abs(x - x_prev) >= eps:
        f_prev = F(x_prev)
        f_x = F(x)
        if f_x - f_prev == 0:
            print("Деление на ноль в методе хорд. Метод не применим.")
            return
        else:
            x_new = x - f_x * (x - x_prev) / (f_x - f_prev)
            x_prev = x
            x = x_new
            k += 1
    print(f"Метод хорд: x = {x}, число итераций = {k}")

print("Введите исходные данные:")
print("Левая граница a = ", end='')
a = float(input())
print("Правая граница b = ", end='')
b = float(input())

if a < b:
    print("Точность eps = ", end='')
    eps = float(input())
    if 0 < eps < 1:
        print("\nВы ввели:")
        print(f"a = {a}\nb = {b}\neps = {eps}")
        print("\nРезультат: ")
        NewtonMethod(a, b, eps)
        ChordMethod(a, b, eps)
    else:
        print("Значения не удовлетворяют условиям")
else:
    print("Значения не удовлетворяют условиям")