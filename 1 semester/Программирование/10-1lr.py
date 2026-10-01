from math import *
from prettytable import PrettyTable
#pip3 install prettytable

tab = PrettyTable(title='Табуляция функции',
                  min_table_width=70)
tab.field_names = ['аргумент x', 'у в радианах', 'у в градусах']

x0 = float(input("x0="))
hx = float(input("hx="))
xn = float(input("xn="))
print(f'x изменяется по закону: {x0} ({hx}) {xn}')

x = x0
while x <= xn + hx/2:
    argument = x + 2.356
    if argument >= 1.0:
        y_rad = acosh(argument)
        y_deg = degrees(y_rad)
        tab.add_row([round(x, 2), y_rad, y_deg])
    else:
        tab.add_row([round(x, 2), 'Нет решения', 'Нет решения'])
    x = x + hx

print(tab)