def is_prime(n):
    """Проверяет, является ли число простым."""
    if n < 2:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True
def get_odd_primes(start, end):
    """Возвращает список нечётных простых чисел в заданном диапазоне."""
    odd_primes = []
    for num in range(start, end + 1):
        if num % 2 != 0 and is_prime(num):
            odd_primes.append(num)
    return odd_primes
def sort_desc(arr):
    """Сортирует массив в порядке убывания (пузырьковая сортировка)."""
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] < arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
start = int(input("Введите начало диапазона: "))
end = int(input("Введите конец диапазона: "))
if start > end:
    start, end = end, start  # Обеспечиваем правильный порядок
odd_primes = get_odd_primes(start, end)
sort_desc(odd_primes)
print("Нечётные простые числа в убывающем порядке:", odd_primes)
