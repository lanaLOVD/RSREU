number = int(input("Введите число: "))
sum_odd = sum(int(digit) for digit in str(number) if int(digit) % 2 != 0)  # вычисление суммы нечетных цифр
print(f"Сумма нечетных цифр: {sum_odd}")

# Перевод в 7-ую систему счисления
n = sum_odd
base_7 = ""
while n > 0:
    base_7 = str(n % 7) + base_7
    n //= 7
base_7 = base_7 or "0"
print(f"Сумма в системе счисления с основанием 7: {base_7}")

# Перемещение первой и последней цифры местами
swapped_base_7 = (base_7[-1] + base_7[1:-1] + base_7[0]) if len(base_7) > 1 else base_7
print(f"После замены первой и последней цифры: {swapped_base_7}")

# Перевод в двоичную систему
n = int(swapped_base_7, 7)
base_2 = bin(n)[2:]  # Перевод в двоичную
print(f"Переведенное в систему счисления с основанием 2: {base_2}")

# Отзеркаливание и перевод в десятичную
decimal_value = int(base_2[::-1], 2)  # Отзеркаливание
print(f"Отзеркаленное число в десятичной системе: {decimal_value}")