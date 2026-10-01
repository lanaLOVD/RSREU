from math import *

nmax = 1e2
print("Введите исходные данные:")
print("z = ", end='')
z = float(input())
print("eps = ", end='')
eps = float(input())

print("Вы ввели:")
print("z = %.2f    eps = %.2e" % (z, eps))

t = -2 * ((1 - z) / (1 + z))
s = t
n = 1

while (fabs(t) > eps) and (n < nmax):
    t = -2 * (1 / (2 * n - 1)) * ((1 - z) / (1 + z)) ** (2 * n - 1)
    s += t
    n += 1

print("n = %d  s = %.5f" % (n, s))  # Исправлено: %d для n, а не %.5f


'''
более правильно:

from math import *

nmax = 100  # 1e2 = 100
print("Введите исходные данные:")
print("z = ", end='')
z = float(input())
print("eps = ", end='')
eps = float(input())

print("Вы ввели:")
print(f"z = {z:.2f}    eps = {eps:.2e}")

t = -2 * ((1 - z) / (1 + z))
s = t
n = 1

while abs(t) > eps and n < nmax:  # abs() вместо fabs()
    t = -2 * (1 / (2 * n - 1)) * ((1 - z) / (1 + z)) ** (2 * n - 1)
    s += t
    n += 1

print(f"n = {n}  s = {s:.5f}")'''