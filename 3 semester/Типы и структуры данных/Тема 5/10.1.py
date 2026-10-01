import sys


class Node:
    __slots__ = ('value', 'count', 'left', 'right')

    def __init__(self, value):
        self.value = value
        self.count = 1  # Счетчик повторений (изначально 1)
        self.left = None
        self.right = None


def inorder_traversal(root, result):
    """
    Рекурсивный ин-ордер обход для вывода элементов
    в порядке возрастания вместе с их частотами.
    """
    if root is None:
        return

    # Сначала левое поддерево (меньшие значения)
    inorder_traversal(root.left, result)

    # Текущий узел: значение и его частота
    result.append(f"{root.value} {root.count}")

    # Затем правое поддерево (большие значения)
    inorder_traversal(root.right, result)


def main():
    data = sys.stdin.read().strip().split()

    if not data or data[0] == '0':
        return

    # Построение дерева с подсчетом частот
    root = None

    for s in data:
        num = int(s)
        if num == 0:
            break

        if root is None:
            root = Node(num)  # Создаем корень с count=1
            continue

        curr = root
        while True:
            if num == curr.value:
                curr.count += 1  # Увеличиваем счетчик для существующего элемента
                break
            elif num < curr.value:
                if curr.left is None:
                    curr.left = Node(num)
                    break
                curr = curr.left
            else:
                if curr.right is None:
                    curr.right = Node(num)
                    break
                curr = curr.right

    # Сбор результата в порядке возрастания значений
    result = []
    inorder_traversal(root, result)

    # Вывод: каждое значение и его частота на отдельной строке
    sys.stdout.write("\n".join(result) + "\n")


if __name__ == "__main__":
    main()