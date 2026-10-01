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
        print(0)
        return

    # Строим дерево
    root = None
    count = 0

    for s in data:
        num = int(s)
        if num == 0:
            break

        if root is None:
            root = Node(num)
            count += 1
            continue

        curr = root
        while True:
            if num == curr.value:
                break  # элемент уже есть
            elif num < curr.value:
                if curr.left is None:
                    curr.left = Node(num)
                    count += 1
                    break
                curr = curr.left
            else:
                if curr.right is None:
                    curr.right = Node(num)
                    count += 1
                    break
                curr = curr.right

    print(count)


if __name__ == "__main__":
    main()