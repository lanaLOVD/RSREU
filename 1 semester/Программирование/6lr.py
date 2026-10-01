print('Введите значение х: ')
y=0
x=float(input())
if x >=0:
    if x <= 1:
        y = x + 5
    elif 1 < x <= 4:
        y =abs(2*((x - 3)**2) - 2)
    elif 4 < x <= 7:
        y = -((x - 3)**(1/2)) + 1
    else:
        print('Не входит')
    print("При x =", x, " функция y =", y)
else:
    print('Точка не удовлетворяет условию')
