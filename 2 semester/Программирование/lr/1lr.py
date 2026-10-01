import timeit
import random
def find_max_negative_sequence(arr):
    max_sequence = []
    current_sequence = []
    for num in arr:
        if num < 0:
            current_sequence.append(num)
        else:
            if len(current_sequence) > len(max_sequence):
                max_sequence = current_sequence
            current_sequence = []
    if len(current_sequence) > len(max_sequence):
        max_sequence = current_sequence
    return max_sequence
def test_algorithm(arr, method_name):
    start_time = timeit.timeit()
    max_sequence = find_max_negative_sequence(arr)
    end_time = timeit.timeit()
    print(f"Метод: {method_name}")
    print(f"Исходный массив: {arr}")
    print(f"Максимальная последовательность отрицательных элементов: {max_sequence}")
    print(f"Время выполнения: {end_time - start_time:.6f} секунд")
    print("-" * 20)
# С использованием разных методов заполнения массива
# Вариант 1: Ввод с клавиатуры
arr1 = []
n = int(input("Введите размер массива: "))
print("Введите элементы массива:")
for i in range(n):
    num = int(input())
    arr1.append(num)
print("Введенный массив:", arr1)
test_algorithm(arr1, "Ввод с клавиатуры")
# Вариант 2: Псевдослучайные числа
arr2 = [random.randint(-10, 10) for _ in range(20)]
test_algorithm(arr2, "Псевдослучайные числа")
# Вариант 3:  Псевдослучайные числа (другой диапазон)
arr3 = [random.randint(-50, 50) for _ in range(30)]
test_algorithm(arr3, "Псевдослучайные числа (другой диапазон)")
# Вариант 4:  Смешанный массив
arr4 = [-1, -2, -3, 0, 1, -4, -5, -6, 2, 3, -7, -8, 0, 4, 5]
test_algorithm(arr4, "Смешанный массив")
