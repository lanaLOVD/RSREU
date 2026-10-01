from math import *
a = 1
b = 2
n = 48

def f(x):
    return (2 * x + sin(x)) / (3 * x ** 2 + 2 * cos(2 * x))

def rectangle_method(a, b, n):
    h = (b - a) / n
    integral_value = 0
    for i in range(n):
        x_mid = a + (i + 0.5) * h  # Находим середину i-го интервала
        integral_value += f(x_mid)  # Значение функции в середине интервала
    integral_value *= h  # Умножаем на ширину интервала
    return integral_value

integral_value = rectangle_method(a, b, n)
print("n = ", n)
print(f"Значение интеграла: {integral_value}")