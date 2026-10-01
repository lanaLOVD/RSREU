import sys


def main():
    # Чтение всех данных из стандартного ввода
    data = sys.stdin.read().strip().split()
    nums = []  # Список для хранения чисел

    # Обработка каждого числа до встречи 0
    for s in data:
        num = int(s)
        if num == 0:  # 0 - признак конца ввода
            break
        nums.append(num)  # Добавляем число в список

    # Если чисел меньше 2, второго максимума нет
    if len(nums) < 2:
        print(0)
        return

    # Убираем дубликаты с помощью множества и сортируем по убыванию
    unique = sorted(set(nums), reverse=True)
    # set(nums) - создает множество (уникальные значения)
    # sorted(..., reverse=True) - сортирует по убыванию

    # Выводим второй элемент (индекс 1) - второй максимум
    print(unique[1])


if __name__ == "__main__":
    main()