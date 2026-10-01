import sys


class Node:
    # Оптимизация памяти: заранее объявляем атрибуты
    __slots__ = ('value', 'left', 'right')

    def __init__(self, value):
        self.value = value  # Значение узла
        self.left = None  # Левый потомок
        self.right = None  # Правый потомок


def main():
    # Чтение всех данных из стандартного ввода
    data = sys.stdin.read().strip().split()

    # Преобразуем строки в числа, останавливаемся на 0
    nums = []
    for s in data:
        num = int(s)
        if num == 0:  # 0 - признак конца ввода
            break
        nums.append(num)

    # Если нет чисел (или только 0)
    if not nums:
        print(0)  # Глубина пустого дерева = 0
        return

    # Создаем корень дерева из первого числа
    root = Node(nums[0])

    # Вставка остальных чисел без балансировки (простое BST)
    for val in nums[1:]:
        curr = root  # Начинаем с корня

        while True:
            if val == curr.value:  # Элемент уже есть
                break
            elif val < curr.value:  # Идем влево
                if curr.left is None:  # Нашли место для вставки
                    curr.left = Node(val)
                    break
                curr = curr.left  # Продолжаем поиск
            else:  # Идем вправо
                if curr.right is None:  # Нашли место для вставки
                    curr.right = Node(val)
                    break
                curr = curr.right  # Продолжаем поиск

    # Подсчет максимальной глубины (высоты) дерева
    max_depth = 0  # Максимальная глубина
    # Используем стек для обхода в глубину (DFS)
    stack = [(root, 1)]  # (узел, текущая глубина)

    while stack:
        node, depth = stack.pop()  # Берем последний добавленный узел

        # Обновляем максимальную глубину
        if depth > max_depth:
            max_depth = depth

        # Добавляем левого потомка в стек (если есть)
        if node.left:
            stack.append((node.left, depth + 1))

        # Добавляем правого потомка в стек (если есть)
        if node.right:
            stack.append((node.right, depth + 1))

    print(max_depth)  # Выводим максимальную глубину дерева