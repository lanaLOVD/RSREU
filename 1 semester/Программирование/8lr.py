from math import *

x0 = -3.356
hx = float(input("Введите шар (hn): "))
xn = -1.356

print(f'x изменяется по закону: {x0} ({hx}) {xn}')
print('%32s' % 'ТАБЛИЦА ЗНАЧЕНИЙ')
print(f'{chr(9484)}{chr(9472)*14}{chr(9516)}{chr(9472)*15}{chr(9516)}{chr(9472)*15}{chr(9488)}')
print(chr(9474) + ' ' * 6 + 'x' + ' ' * 7 + chr(9474) + ' ' * 2 + 'y (B pad.)' + ' ' * 3 + chr(9474) + ' ' * 2 + 'y (B grad.)' + ' ' * 2 + chr(9474))
print(chr(9500) + chr(9472) * 14 + chr(9474) + chr(9472) * 15 + chr(9474) + chr(9472) * 15 + chr(9508))

x = x0
while x <= xn + hx / 2:
    argument = x + 2.356
    if argument >= 1:
        y_rad = acosh(argument)
        y_deg = degrees(y_rad)
        # Исправлено: x_deg -> y_deg
        print(chr(9474) + " %4.4f    " % (x) + chr(9474) + " %2.3e    " % (y_rad) + chr(9474) + " %2.3e    " % (y_deg) + chr(9474))
    else:
        print(chr(9474) + " %4.4f    " % (x) + chr(9474) + " " + chr(9474) + " " + chr(9474) + " " + str(9474))
    x += hx
    if x <= xn + hx / 2:
        print(chr(9500) + chr(9472) * 14 + chr(9474) + chr(9472) * 15 + chr(9474) + chr(9472) * 15 + chr(9508))

print(chr(9492) + chr(9472) * 14 + chr(9496) + chr(9472) * 15 + chr(9496) + chr(9472) * 15 + chr(9498))