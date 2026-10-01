def can_reach(N, A, B, current=1):  # Зависимый случай: если текущее число равно N, то это достижимо
    if current == N:
        return True
    # Если текущее число больше N, то путь невозможен
    if current > N:
        return False
    # Рекурсивно проверяем два случая: прибавить A или прибавить B
    gig = can_reach(N, A, B, current + A) or can_reach(N, A, B, current + B)
    return gig

N = int(input("Введите число N: "))
A = int(input("Введите значение A: "))
B = int(input("Введите значение B: "))

if N >= 1 and A >= 1 and B >= 1:
    if can_reach(N, A, B):
        print(f"Можно достичь числа {N} из 1, используя операции прибавить {A} и прибавить {B}.")
    else:
        print(f"Невозможно достичь числа {N} из 1, используя операции прибавить {A} и прибавить {B}.")
else:
    print('Значения не удовлетворяют условиям')