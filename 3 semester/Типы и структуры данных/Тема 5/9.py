import sys


class Node:
    __slots__ = ('value', 'left', 'right')

    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


def is_balanced(root):
    """Проверяет сбалансированность дерева. Возвращает (сбалансировано, высота)."""
    if root is None:
        return True, 0

    left_balanced, left_height = is_balanced(root.left)
    if not left_balanced:
        return False, 0

    right_balanced, right_height = is_balanced(root.right)
    if not right_balanced:
        return False, 0

    # Проверяем разницу высот
    if abs(left_height - right_height) > 1:
        return False, 0

    # Высота текущего поддерева
    height = max(left_height, right_height) + 1
    return True, height


def main():
    data = sys.stdin.read().strip().split()

    if not data or data[0] == '0':
        print("YES")
        return

    # Построение дерева
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
                break  # дубликат не добавляем
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

    # Проверка сбалансированности
    balanced, _ = is_balanced(root)
    print("YES" if balanced else "NO")


if __name__ == "__main__":
    main()