import sys


class Node:
    __slots__ = ('value', 'count', 'left', 'right')

    def __init__(self, value):
        self.value = value
        self.count = 1  # счетчик повторений
        self.left = None
        self.right = None


def inorder_traversal(root, result):
    """Ин-ордер обход для вывода элементов в порядке возрастания."""
    if root is None:
        return

    inorder_traversal(root.left, result)
    result.append(f"{root.value} {root.count}")
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
            root = Node(num)
            continue

        curr = root
        while True:
            if num == curr.value:
                curr.count += 1  # увеличиваем счетчик для существующего элемента
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

    # Сбор результата в порядке возрастания
    result = []
    inorder_traversal(root, result)

    # Вывод
    sys.stdout.write("\n".join(result) + "\n")


if __name__ == "__main__":
    main()