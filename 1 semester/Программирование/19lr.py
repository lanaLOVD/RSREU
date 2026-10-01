from math import *
from random import *

def F(x):
    i = 4 * x**3 + x - 1
    return i

def MKarlo(a, b, eps):  # Метод Монте-Карло
    k = 0
    while abs(b - a) >= eps:
        xn = a + (b - a) * random()
        if F(a) * F(xn) < 0:
            b = xn
        else:
            a = xn
        k += 1
    x = (a + b) / 2
    print(f"x = {x}")
    print(f"Число итераций = {k}")

def PoDel(a, b, eps):  # Метод половинного деления
    k = 0
    while abs(b - a) >= eps:
        c = (a + b) / 2
        fc = F(c)
        if F(a) * fc < 0:
            b = c
        else:
            a = c
        k += 1
    x = (a + b) / 2
    print(f"x = {x}")
    print(f"Число итераций = {k}")

print("Введите исходные данные:")
print("Левая граница a = ", end=' ')
a = float(input())
print("Правая граница b = ", end=' ')
b = float(input())

if a < b:
    print("Точность eps = ", end=' ')
    eps = float(input())
    if 0 < eps < 1:
        print("\nВы ввели:")
        print(f"a = {a}\nb = {b}\neps = {eps}")
        print("\nМетод половинного деления:")
        PoDel(a, b, eps)
        print("\nМетод Монте-Карло:")
        MKarlo(a, b, eps)
    else:
        print("Значения не удовлетворяют условиям")
else:
    print("Значения не удовлетворяют условиям")