from math import *

x0 = -3.356
hx = float(input('Введите шар по X: '))
xn = -1.356
print(f'x изменяется по закону: {x0} ({hx}) {xn}')

print('┌─────────────┬─────────────┬─────────────┐')
print('│     x       │   В рад.    │   В град.   │')
print('├─────────────┼─────────────┼─────────────┤')

x = x0

while True:
    argument = x + 2.356
    if argument < 1.0:
        print('│ x = %4.3f   │  нет реш.   │  нет реш.   │' % x)
    else:
        y_rad = acosh(argument)
        y_deg = degrees(y_rad)
        print('│ x = %4.3f   │ y = %2.3e │ y = %2.3e │' % (x, y_rad, y_deg))
    x += hx
    if x > xn + hx/2:
        break

print('└─────────────┴─────────────┴─────────────┘')