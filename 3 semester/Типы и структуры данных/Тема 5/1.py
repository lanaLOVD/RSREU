import sys

class TreeNode:
    def __init__(self, val: int):
        self.value = val
        self.left = None
        self.right = None


class BinarySearchTree:
    def __init__(self):
        self.root = None

    def _add(self, node: TreeNode, value: int) -> tuple[TreeNode, bool]:
        if not node:
            return TreeNode(value), False

        if value == node.value:
            return node, True

        if value < node.value:
            node.left, already_exists = self._add(node.left, value)
        else:
            node.right, already_exists = self._add(node.right, value)

        return node, already_exists

    def _search(self, node: TreeNode, value: int) -> bool:
        if not node:
            return False

        if value == node.value:
            return True

        if value < node.value:
            return self._search(node.left, value)
        else:
            return self._search(node.right, value)

    def _find_max(self, node: TreeNode) -> TreeNode:
        while node and node.right:
            node = node.right
        return node

    def _delete_node(self, node: TreeNode, value: int) -> tuple[TreeNode, bool]:
        if not node:
            return None, False

        found = False
        if value < node.value:
            node.left, found = self._delete_node(node.left, value)
        elif value > node.value:
            node.right, found = self._delete_node(node.right, value)
        else:
            found = True
            if not node.left:
                return node.right, found
            elif not node.right:
                return node.left, found
            else:
                max_left = self._find_max(node.left)
                node.value = max_left.value
                node.left, _ = self._delete_node(node.left, max_left.value)

        return node, found

    def _print_tree(self, node: TreeNode, level: int) -> None:
        if not node:
            return
        self._print_tree(node.left, level + 1)
        print("." * level + str(node.value))
        self._print_tree(node.right, level + 1)

    def add(self, value: int) -> str:
        self.root, already_exists = self._add(self.root, value)
        return "ALREADY" if already_exists else "DONE"

    def delete(self, value: int) -> str:
        self.root, found = self._delete_node(self.root, value)
        return "DONE" if found else "CANNOT"

    def search(self, value: int) -> str:
        return "YES" if self._search(self.root, value) else "NO"

    def print_tree(self) -> None:
        self._print_tree(self.root, 0)



tree = BinarySearchTree()
for line in sys.stdin:
    parts = line.strip().split()
    if not parts:
        continue
    command = parts[0]
    if command == "ADD":
        value = int(parts[1])
        print(tree.add(value))
    elif command == "DELETE":
        value = int(parts[1])
        print(tree.delete(value))
    elif command == "SEARCH":
        value = int(parts[1])
        print(tree.search(value))
    elif command == "PRINTTREE":
        tree.print_tree()

