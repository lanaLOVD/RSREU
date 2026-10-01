import random
def generate_matrix(rows, cols):
    """Создаёт матрицу случайных чисел в диапазоне [0.9, 1.3]"""
    return [[round(random.uniform(0.9, 1.3), 2) for _ in range(cols)] for _ in range(rows)]
def sum_rows(matrix):
    """Вычисляет сумму элементов в каждой строке"""
    return [sum(row) for row in matrix]
def normalize_matrix(matrix, row_sums):
    """Нормализует элементы матрицы, деля их на сумму соответствующей строки"""
    return [[round(value / row_sums[i], 4) for value in row] for i, row in enumerate(matrix)]
def print_matrix(matrix, title):
    """Выводит матрицу"""
    print(title)
    for row in matrix:
        print("  ".join(f"{num:6.4f}" for num in row))
# Создание и обработка матрицы A
rows_a, cols_a = 4, 5
matrix_a = generate_matrix(rows_a, cols_a)
print_matrix(matrix_a, "Матрица A:")
sum_a = sum_rows(matrix_a)
norm_a = normalize_matrix(matrix_a, sum_a)
print_matrix(norm_a, "Нормализованная матрица A:")
# Создание и обработка матрицы B
rows_b, cols_b = 3, 4
matrix_b = generate_matrix(rows_b, cols_b)
print_matrix(matrix_b, "Матрица B:")
sum_b = sum_rows(matrix_b)
norm_b = normalize_matrix(matrix_b, sum_b)
print_matrix(norm_b, "Нормализованная матрица B:")
