from math import *

x0 = float(input("Введите начальное значение для x (x0): "))
hx = float(input("Введите шаг (hn): "))
xn = float(input("Введите конечное значение для x (xn): "))
print(f"x изменяется по закону: {x0} ({hx}) {xn}")

if hx > 0 and x0 < xn:
    # Вывод шапки таблицы
    print(f'{chr(9484)}{chr(9472) * 14}{chr(9516)}{chr(9472) * 15}{chr(9516)}{chr(9472) * 15}{chr(9488)}')
    print(chr(9474) + ' ' * 6 + 'x' + ' ' * 7 + chr(9474) + ' ' * 2 + 'y (B рад.)' + ' ' * 3 + chr(
        9474) + ' ' * 2 + 'y (B град.)' + ' ' * 2 + chr(9474))
    print(chr(9500) + chr(9472) * 14 + chr(9474) + chr(9472) * 15 + chr(9474) + chr(9472) * 15 + chr(9508))

    x = x0
    repeats = int((xn - x0) / hx) + 1  # Количество итераций

    for i in range(repeats):
        argument = x + 2.356
        if argument >= 1.0:
            y_rad = acosh(argument)
            y_deg = degrees(y_rad)
            print(chr(9474) + "    %4.3f    " % (x) + chr(9474) + "    %2.3e    " % (y_rad) + chr(
                9474) + "    %2.3e    " % (y_deg) + chr(9474))
        else:
            print(
                chr(9474) + "    %4.3f    " % (x) + chr(9474) + "  Нет решения  " + chr(9474) + "  Нет решения  " + chr(
                    9474))

        x += hx

        if i < repeats - 1:
            print(chr(9500) + chr(9472) * 14 + chr(9474) + chr(9472) * 15 + chr(9474) + chr(9472) * 15 + chr(9508))

    print(chr(9492) + chr(9472) * 14 + chr(9496) + chr(9472) * 15 + chr(9496) + chr(9472) * 15 + chr(9498))
else:
    print("Введенные значения не удовлетворяют условиям (требуется hx > 0 и x0 < xn)")