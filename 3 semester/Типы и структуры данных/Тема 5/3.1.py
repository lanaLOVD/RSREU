import sys


class Node:
    # Оптимизация памяти
    __slots__ = ('value', 'left', 'right')

    def __init__(self, value):
        self.value = value  # Значение узла
        self.left = None  # Левый потомок
        self.right = None  # Правый потомок


def main():
    # Чтение всех данных
    data = sys.stdin.read().strip().split()

    # Если нет данных или первый элемент 0
    if not data or data[0] == '0':
        print(0)  # Количество уникальных элементов = 0
        return

    root = None  # Корень дерева
    count = 0  # Счетчик уникальных элементов

    # Обрабатываем каждое число
    for s in data:
        num = int(s)
        if num == 0:  # 0 - признак конца ввода
            break

        # Если дерево пустое
        if root is None:
            root = Node(num)  # Создаем корень
            count += 1  # Увеличиваем счетчик
            continue

        # Ищем место для вставки
        curr = root
        while True:
            if num == curr.value:  # Элемент уже есть
                break  # Не увеличиваем счетчик

            elif num < curr.value:  # Идем влево
                if curr.left is None:  # Нашли место
                    curr.left = Node(num)
                    count += 1  # Увеличиваем счетчик
                    break
                curr = curr.left  # Продолжаем поиск

            else:  # Идем вправо
                if curr.right is None:  # Нашли место
                    curr.right = Node(num)
                    count += 1  # Увеличиваем счетчик
                    break
                curr = curr.right  # Продолжаем поиск

    print(count)  # Выводим количество уникальных элементов