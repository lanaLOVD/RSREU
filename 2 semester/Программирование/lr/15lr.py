import random
import string
from collections import Counter
# Запрос режима работы программы
mode = int(input("Введите режим (1 для генерации данных, 2 для обработки данных): "))
if mode == 1:
    # Генерация данных
    num_lines = int(input("Введите количество строк для генерации: "))
    # Создаём файл Data.txt и записываем строки
    with open('Data.txt', 'w') as file:
        for i in range(num_lines):
            # Генерация случайной строки
            symbols = string.ascii_uppercase + string.digits
            length = random.randint(10, 100)  # Длина строки от 10 до 100
            line = ''.join(random.choice(symbols) for _ in range(length))
            file.write(line + '\n')
    print(f"Файл Data.txt успешно создан с {num_lines} строками.")
elif mode == 2:
    # Обработка данных из файла Data.txt
    with open('Data.txt', 'r') as file:
        lines = file.readlines()
    max_even_count = -1
    target_line = ''
    target_line_index = -1
    # Ищем строку с максимальным количеством чётных чисел
    for idx, line in enumerate(lines):
        even_count = sum(1 for char in line if char.isdigit() and int(char) % 2 == 0)
        if even_count > max_even_count:
            max_even_count = even_count
            target_line = line
            target_line_index = idx
    if target_line_index == -1:
        print("Не найдено строк с чётными цифрами.")
    else:
        # Подсчитываем частоту букв в строке
        letter_counts = Counter(c for c in target_line if c.isalpha())
        # Записываем результат в файл Result.txt
        with open('Result.txt', 'w') as result_file:
            result_file.write(
                f"Строка с максимальным количеством чётных чисел (строка {target_line_index + 1}): {target_line}\n")
            result_file.write("Частота букв в этой строке:\n")
            for letter, count in letter_counts.items():
                result_file.write(f"{letter}: {count}\n")
        print(f"Обработка завершена. Результаты записаны в Result.txt.")
else:
    print("Некорректный режим.")

