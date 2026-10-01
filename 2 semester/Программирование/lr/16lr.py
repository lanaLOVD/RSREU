def print_matrix(matrix):
    for row in matrix:
        print(row)
def sum_columns(matrix):
    num_columns = len(matrix[0])
    sums = [0] * num_columns
    for row in matrix:
        for i in range(num_columns):
            sums[i] += row[i]
    return sums
def sort_rows(matrix):
    for i in range(len(matrix)):
        matrix[i].sort(reverse=True)
    return matrix
def compare_matrices(matrix1, matrix2):
    if len(matrix1) != len(matrix2) or len(matrix1[0]) != len(matrix2[0]):
        return False
    for i in range(len(matrix1)):
        for j in range(len(matrix1[0])):
            if matrix1[i][j] != matrix2[i][j]:
                return False
    return True
def swap_min_elements(matrix1, matrix2):
    min1, min2 = float('inf'), float('inf')
    min_pos1, min_pos2 = (-1, -1), (-1, -1)
    for i in range(len(matrix1)):
        for j in range(len(matrix1[0])):
            if matrix1[i][j] < min1:
                min1 = matrix1[i][j]
                min_pos1 = (i, j)
            if matrix2[i][j] < min2:
                min2 = matrix2[i][j]
                min_pos2 = (i, j)

    matrix1[min_pos1[0]][min_pos1[1]], matrix2[min_pos2[0]][min_pos2[1]] = min2, min1
    return matrix1, matrix2
matrix1 = [
    [3, 2, 1],
    [9, 4, 8],
    [7, 5, 6]
]
matrix2 = [
    [6, 5, 4],
    [2, 3, 1],
    [8, 7, 9]
]
while True:
    print("\nМеню:")
    print("1. Сумма элементов каждого столбца матрицы")
    print("2. Сортировка элементов каждой строки матрицы по убыванию")
    print("3. Проверка, что матрицы состоят из одинаковых элементов")
    print("4. Замена местами минимальных элементов двух матриц")
    print("5. Выход")
    choice = input("Выберите номер функции: ")
    if choice == "1":
        column_sums = sum_columns(matrix1)
        print(f"Сумма элементов каждого столбца: {column_sums}")
    elif choice == "2":
        sorted_matrix = sort_rows(matrix1)
        print("Матрица после сортировки строк по убыванию:")
        print_matrix(sorted_matrix)
    elif choice == "3":
        are_equal = compare_matrices(matrix1, matrix2)
        print("Матрицы одинаковые?" , "Да" if are_equal else "Нет")
    elif choice == "4":
        matrix1, matrix2 = swap_min_elements(matrix1, matrix2)
        print("Матрица 1 после обмена минимальными элементами:")
        print_matrix(matrix1)
        print("Матрица 2 после обмена минимальными элементами:")
        print_matrix(matrix2)
    elif choice == "5":
        print("Выход из программы.")
        break
    else:
        print("Некорректный выбор. Попробуйте снова.")


