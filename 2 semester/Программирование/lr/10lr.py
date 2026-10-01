import numpy as np
def f(x):
    return np.cos(x) + x / 10
def df(x):
    return -np.sin(x) + 1 / 10
def d2f(x):
    return -np.cos(x)
# Метод дихотомии
def dichotomy_method(func, a, b, epsilon=1e-3, delta=None):
    if delta is None:
        delta = epsilon / 2
    iterations = 0
    print("\nДихотомия: первые 5 итераций интервалов")
    while (b - a) / 2 > epsilon:
        if iterations < 5:
            print(f"Итерация {iterations + 1}: a = {a:.6f}, b = {b:.6f}")
        x1 = (a + b) / 2 - delta
        x2 = (a + b) / 2 + delta
        f1 = func(x1)
        f2 = func(x2)
        if f1 > f2:
            b = x2
        else:
            a = x1
        iterations += 1
    x_max = (a + b) / 2
    return x_max, func(x_max), iterations
# Метод золотого сечения
def golden_section_method(func, a, b, epsilon=1e-3):
    phi = (1 + np.sqrt(5)) / 2
    resphi = 2 - phi
    x1 = a + resphi * (b - a)
    x2 = b - resphi * (b - a)
    f1 = func(x1)
    f2 = func(x2)
    iterations = 0
    print("\nЗолотое сечение: первые 5 итераций интервалов")
    while abs(b - a) > epsilon:
        if iterations < 5:
            print(f"Итерация {iterations + 1}: a = {a:.6f}, b = {b:.6f}")
        if f1 > f2:
            b = x2
            x2 = x1
            f2 = f1
            x1 = a + resphi * (b - a)
            f1 = func(x1)
        else:
            a = x1
            x1 = x2
            f1 = f2
            x2 = b - resphi * (b - a)
            f2 = func(x2)
        iterations += 1
    x_max = (a + b) / 2
    return x_max, func(x_max), iterations

# Метод Фибоначчи
def fibonacci_numbers(n):
    fib = [1, 1]
    while len(fib) < n:
        fib.append(fib[-1] + fib[-2])
    return fib

def fibonacci_method(func, a, b, epsilon=1e-3):
    n = 1
    while fibonacci_numbers(n)[-1] < (b - a) / epsilon:
        n += 1
    fib = fibonacci_numbers(n + 1)
    x1 = a + (fib[n - 2] / fib[n]) * (b - a)
    x2 = a + (fib[n - 1] / fib[n]) * (b - a)
    f1 = func(x1)
    f2 = func(x2)
    iterations = 0
    print("\nФибоначчи: первые 5 итераций интервалов")
    for k in range(1, n - 1):
        if iterations < 5:
            print(f"Итерация {iterations + 1}: a = {a:.6f}, b = {b:.6f}")
        if f1 < f2:
            a = x1
            x1 = x2
            f1 = f2
            x2 = a + (fib[n - k - 1] / fib[n - k]) * (b - a)
            f2 = func(x2)
        else:
            b = x2
            x2 = x1
            f2 = f1
            x1 = a + (fib[n - k - 2] / fib[n - k]) * (b - a)
            f1 = func(x1)
        iterations += 1
    x_max = (x1 + x2) / 2
    return x_max, func(x_max), iterations

# Метод Ньютона
def newton_method(func, dfunc, d2func, x0, epsilon=1e-6, max_iter=100):
    x = x0
    iterations = 0
    print("\nНьютон: первые 5 итераций интервалов")
    for _ in range(max_iter):
        dfx = dfunc(x)
        d2fx = d2func(x)
        if iterations < 4:
            print(f"Итерация {iterations + 1}: a = {a:.6f}, b = {b:.6f}")
        if abs(dfx) < epsilon:
            break
        if d2fx == 0:
            print("Ошибка: вторая производная равна нулю.")
            break
        x_new = x - dfx / d2fx
        if abs(x_new - x) < epsilon:
            x = x_new
            break
        x = x_new
        iterations += 1
    return x, func(x), iterations

# Границы поиска
a = 0
b = np.pi

# Запуск всех методов
x_max, f_max, iterations = dichotomy_method(f, a, b)
print(f"\nМетод дихотомии: x = {x_max:.6f}, f(x) = {f_max:.6f}, итераций: {iterations}")

x_max, f_max, iterations = golden_section_method(f, a, b)
print(f"\nМетод золотого сечения: x = {x_max:.6f}, f(x) = {f_max:.6f}, итераций: {iterations}")

x_max, f_max, iterations = fibonacci_method(f, a, b)
print(f"\nМетод Фибоначчи: x = {x_max:.6f}, f(x) = {f_max:.6f}, итераций: {iterations}")

x_max, f_max, iterations = newton_method(f, df, d2f, x0=1.0)
print(f"\nМетод Ньютона: x = {x_max:.6f}, f(x) = {f_max:.6f}, итераций: {iterations}")

