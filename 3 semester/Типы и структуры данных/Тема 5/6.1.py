import sys

class Node:
    __slots__ = ('value', 'left', 'right')

    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def main():
    data = sys.stdin.read().strip().split()

    if not data or data[0] == '0':
        return

    # Построение дерева (аналогично 5.py)
    root = None

    for s in data:
        num = int(s)
        if num == 0:
            break

        if root is None:
            root = Node(num)
            continue

        curr = root
        while True:
            if num == curr.value:
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

    # Итеративный ин-ордер обход для сбора листьев
    leaves = []  # Список для хранения листьев
    stack = []   # Стек для обхода
    curr = root  # Начинаем с корня

    while stack or curr:
        # Идем до самого левого узла
        while curr:
            stack.append(curr)
            curr = curr.left

        # Извлекаем узел из стека
        curr = stack.pop()

        # Проверяем, является ли узел листом
        # Лист - узел без потомков
        if curr.left is None and curr.right is None:
            leaves.append(curr.value)  # Добавляем значение листа

        # Переходим к правому поддереву
        curr = curr.right

    # Вывод листьев
    sys.stdout.write("\n".join(map(str, leaves)) + "\n")

if __name__ == "__main__":
    main()