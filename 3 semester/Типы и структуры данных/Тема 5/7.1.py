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

    # Построение дерева (аналогично 5.py и 6.py)
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

    # Итеративный ин-ордер обход для сбора развилок
    forks = []  # Список для хранения развилок
    stack = []  # Стек для обхода
    curr = root # Начинаем с корня

    while stack or curr:
        # Идем до самого левого узла
        while curr:
            stack.append(curr)
            curr = curr.left

        # Извлекаем узел из стека
        curr = stack.pop()

        # Проверяем, является ли узел развилкой
        # Развилка - узел с обоими потомками
        if curr.left is not None and curr.right is not None:
            forks.append(curr.value)  # Добавляем значение развилки

        # Переходим к правому поддереву
        curr = curr.right

    # Вывод развилок
    sys.stdout.write("\n".join(map(str, forks)) + "\n")

if __name__ == "__main__":
    main()