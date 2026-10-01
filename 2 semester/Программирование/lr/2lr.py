import timeit
import random
def generate_matrix_manual():
    matrix = []
    print("Введите 8 строк по 3 числа через пробел:")
    for i in range(8):
        row = list(map(float, input(f"Строка {i + 1}: ").split()))
        matrix.append(row)
    return matrix
def generate_matrix_random():
    return [[random.uniform(1, 100) for _ in range(3)] for _ in range(8)]
def process_matrix_without_list_methods(matrix):
    start_time = timeit.timeit()
    avg_values = []
    for row in matrix:
        total = 0
        for value in row:
            total += value
        avg_values.append(total / len(row))
    # Сортировка без встроенных методов
    for i in range(len(avg_values)):
        for j in range(i + 1, len(avg_values)):
            if avg_values[i] > avg_values[j]:
                avg_values[i], avg_values[j] = avg_values[j], avg_values[i]
    first_half_sum = sum(avg_values[:len(avg_values) // 2])
    second_half_sum = sum(avg_values[len(avg_values) // 2:])
    ratio = second_half_sum / first_half_sum if first_half_sum != 0 else float('inf')
    # Инверсия массива
    for i in range(len(avg_values) // 2):
        avg_values[i], avg_values[-i - 1] = avg_values[-i - 1], avg_values[i]
    avg_of_avg = sum(avg_values) / len(avg_values)
    closest_value = avg_values[0]
    min_diff = abs(avg_values[0] - avg_of_avg)
    for value in avg_values:
        if abs(value - avg_of_avg) < min_diff:
            min_diff = abs(value - avg_of_avg)
            closest_value = value
    end_time = timeit.timeit()
    return avg_values, ratio, closest_value, end_time - start_time
def process_matrix_with_list_methods(matrix):
    start_time = timeit.timeit()
    avg_values = [sum(row) / len(row) for row in matrix]
    avg_values.sort()
    first_half_sum = sum(avg_values[:len(avg_values) // 2])
    second_half_sum = sum(avg_values[len(avg_values) // 2:])
    ratio = second_half_sum / first_half_sum if first_half_sum != 0 else float('inf')
    avg_values.reverse()
    avg_of_avg = sum(avg_values) / len(avg_values)
    closest_value = min(avg_values, key=lambda x: abs(x - avg_of_avg))
    end_time = timeit.timeit()
    return avg_values, ratio, closest_value, end_time - start_time
# Выбор способа генерации матрицы
option = input("Выберите способ заполнения (1 - вручную, 2 - случайные числа): ")
if option == "1":
    matrix = generate_matrix_manual()
else:
    matrix = generate_matrix_random()
    for row in matrix:
        print(" ".join(map(str, row)))
# Обработка без методов списка
result1, ratio1, closest1, time1 = process_matrix_without_list_methods(matrix)
print(f"Результат без методов списка: {result1}")
print(f"Отношение сумм половин: {ratio1}")
print(f"Ближайший к среднему элемент: {closest1}")
print(f"Время выполнения: {time1:.6f} секунд")
# Обработка с методами списка
result2, ratio2, closest2, time2 = process_matrix_with_list_methods(matrix)
print(f"Результат с методами списка: {result2}")
print(f"Отношение сумм половин: {ratio2}")
print(f"Ближайший к среднему элемент: {closest2}")
print(f"Время выполнения: {time2:.6f} секунд")
# Сравнение времени выполнения
print(f"Методы списка работают быстрее в {time1 / time2:.2f} раза")

