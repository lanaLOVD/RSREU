import sys
from math import *

def f1(x: float):
    return x**3
def f2(x: float):
    return 5*x - 1
def f3(x: float):
    return 3*(x**3) + x + 2
def f4(x: float):
    return 7*(x**5.5)
def f5(x: float):
    return ((2*x)**(1/5))

print('Функции:')
print('1) f(x)=x^3')
print('2) f(x)=5x - 1')
print('3) f(x)=3x^3 +x+2')
print('4) f(x)=7x^5.5')
print('5) f(x)=(2x)^(1/5)')

x = float(input('Введите х: '))
fj = str(input(('Введите fj(x) (1-5):')))

match fj:
    case '1':
        fj = f1(x)
    case '2':
        fj = f2(x)
    case '3':
        fj = f3(x)
    case '4':
        fj = f4(x)
    case '5':
        fj = f5(x)
    case _:
        sys.exit('В списке нет такой функции')

print('Функция fj(x):', fj)
fi = str(input(('Выберите fi(fj(x)) (1-5): ')))

match fi:
    case '1':
        fi = f1(fj)
    case '2':
        fi = f2(fj)
    case '3':
        fi = f3(fj)
    case '4':
        fi = f4(fj)
    case '5':
        fi = f5(fj)
    case _:
        sys.exit('В списке нет такой функции')

print('Функция fi(fj(x)) =', fi)
