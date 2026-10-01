import sys


class Node:
    __slots__ = ('value', 'left', 'right')

    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


def main():
    data = sys.stdin.read().strip().split()
    nums = []
    for s in data:
        num = int(s)
        if num == 0:
            break
        nums.append(num)

    if not nums:
        print(0)
        return

    root = Node(nums[0])

    # Вставка без балансировки
    for val in nums[1:]:
        curr = root
        while True:
            if val == curr.value:
                break
            elif val < curr.value:
                if curr.left is None:
                    curr.left = Node(val)
                    break
                curr = curr.left
            else:
                if curr.right is None:
                    curr.right = Node(val)
                    break
                curr = curr.right

    # Подсчет уровней итеративно (DFS со стеком)
    max_depth = 0
    stack = [(root, 1)]  # (узел, текущая глубина)
    while stack:
        node, depth = stack.pop()
        if depth > max_depth:
            max_depth = depth
        if node.left:
            stack.append((node.left, depth + 1))
        if node.right:
            stack.append((node.right, depth + 1))

    print(max_depth)


if __name__ == "__main__":
    main()