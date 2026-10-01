import timeit
import random
import numpy as np
#pip3 install numpy

# Функция для создания матрицы случайными числами
def generate_matrix(rows, cols):
    return [[round(random.uniform(0.9, 1.3), 2) for _ in range(cols)] for _ in range(rows)]

# Функция для ввода матрицы вручную
def input_matrix(rows, cols):
    matrix = []
    for i in range(rows):
        row = []
        for j in range(cols):
            value = float(input(f"Введите элемент [{i+1},{j+1}]: "))
            row.append(value)
        matrix.append(row)
    return matrix

# Функция вычисления суммы строк и нормализации элементов
def process_matrix(matrix):
    row_sums = [sum(row) for row in matrix]  # Считаем сумму строк
    normalized_matrix = [[round(elem / row_sums[i], 4) for elem in row] for i, row in enumerate(matrix)]
    return row_sums, normalized_matrix

# Запуск без numpy
def main_without_numpy():
    print("Создание матрицы A (4x5) случайными значениями...")
    matrix_a = generate_matrix(4, 5)
    print("Матрица A:", matrix_a)
    print("Создание матрицы B (3x4) случайными значениями...")
    matrix_b = generate_matrix(3, 4)
    print("Матрица B:", matrix_b)
    start_time = timeit.default_timer()
    sum_a, norm_a = process_matrix(matrix_a)
    sum_b, norm_b = process_matrix(matrix_b)
    end_time = timeit.default_timer()
    print("Суммы строк матрицы A:", sum_a)
    print("Нормализованная матрица A:", norm_a)
    print("Суммы строк матрицы B:", sum_b)
    print("Нормализованная матрица B:", norm_b)
    return end_time - start_time

# Замер времени для работы без numpy
time_without_numpy = main_without_numpy()
print(f"Время выполнения без numpy: {time_without_numpy:.6f} секунд")

# Функция для генерации случайных матриц с numpy
def generate_matrix_np(rows, cols):
    return np.round(np.random.uniform(0.9, 1.3, size=(rows, cols)), 2)

# Функция для ввода матрицы вручную с numpy
def input_matrix_np(rows, cols):
    matrix = []
    for i in range(rows):
        row = [float(input(f"Введите элемент [{i+1},{j+1}]: ")) for j in range(cols)]
        matrix.append(row)
    return np.array(matrix)

# Запуск с numpy
def main_with_numpy():
    print("Создание матрицы A (4x5) с numpy...")
    matrix_a = generate_matrix_np(4, 5)
    print("Матрица A:\n", matrix_a)
    print("Создание матрицы B (3x4) с numpy...")
    matrix_b = generate_matrix_np(3, 4)
    print("Матрица B:\n", matrix_b)
    start_time = timeit.default_timer()
    sum_a = np.sum(matrix_a, axis=1, keepdims=True)
    norm_a = np.round(matrix_a / sum_a, 4)
    sum_b = np.sum(matrix_b, axis=1, keepdims=True)
    norm_b = np.round(matrix_b / sum_b, 4)
    end_time = timeit.default_timer()
    print("Суммы строк матрицы A:\n", sum_a.flatten())
    print("Нормализованная матрица A:\n", norm_a)
    print("Суммы строк матрицы B:\n", sum_b.flatten())
    print("Нормализованная матрица B:\n", norm_b)
    return end_time - start_time

# Замер времени для работы с numpy
time_with_numpy = main_with_numpy()
print(f"Время выполнения с numpy: {time_with_numpy:.6f} секунд")

# Сравнение времени выполнения
print(f"Разница во времени: {abs(time_without_numpy - time_with_numpy):.6f} секунд")