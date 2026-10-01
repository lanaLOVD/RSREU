import sys

class Node:
    __slots__ = ('value', 'left', 'right')

    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def is_balanced(root):
    """
    Проверяет сбалансированность дерева.
    Возвращает пару (сбалансировано?, высота поддерева).
    """
    if root is None:  # Пустое дерево сбалансировано
        return True, 0

    # Рекурсивно проверяем левое поддерево
    left_balanced, left_height = is_balanced(root.left)
    if not left_balanced:  # Если левое не сбалансировано
        return False, 0    # Все дерево не сбалансировано

    # Рекурсивно проверяем правое поддерево
    right_balanced, right_height = is_balanced(root.right)
    if not right_balanced:  # Если правое не сбалансировано
        return False, 0     # Все дерево не сбалансировано

    # Проверяем разницу высот левого и правого поддеревьев
    if abs(left_height - right_height) > 1:
        return False, 0  # Разница высот > 1 - дерево не сбалансировано

    # Высота текущего поддерева = максимальная высота потомков + 1
    height = max(left_height, right_height) + 1
    return True, height  # Дерево сбалансировано

def main():
    data = sys.stdin.read().strip().split()

    if not data or data[0] == '0':
        print("YES")  # Пустое дерево считается сбалансированным
        return

    # Построение дерева (стандартное)
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
                break  # Игнорируем дубликаты
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