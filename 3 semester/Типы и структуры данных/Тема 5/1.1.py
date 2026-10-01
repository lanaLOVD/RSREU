import sys


class TreeNode:
    def __init__(self, val: int):
        self.value = val  # Значение узла
        self.left = None  # Левый потомок (меньшие значения)
        self.right = None  # Правый потомок (большие значения)


class BinarySearchTree:
    def __init__(self):
        self.root = None  # Корень дерева (изначально дерево пустое)

    # Рекурсивное добавление узла в дерево
    def _add(self, node: TreeNode, value: int) -> tuple[TreeNode, bool]:
        # Базовый случай: если дошли до пустого места
        if not node:
            # Создаем новый узел и возвращаем его
            # False означает, что элемент не существовал ранее
            return TreeNode(value), False

        # Если значение уже есть в дереве
        if value == node.value:
            # Возвращаем тот же узел и True (элемент уже существует)
            return node, True

        # Если новое значение меньше текущего узла
        if value < node.value:
            # Рекурсивно добавляем в левое поддерево
            node.left, already_exists = self._add(node.left, value)
        else:
            # Иначе добавляем в правое поддерево
            node.right, already_exists = self._add(node.right, value)

        # Возвращаем текущий узел и флаг существования
        return node, already_exists

    # Рекурсивный поиск значения в дереве
    def _search(self, node: TreeNode, value: int) -> bool:
        # Базовый случай: узел не найден
        if not node:
            return False

        # Если нашли нужное значение
        if value == node.value:
            return True

        # Если искомое значение меньше текущего
        if value < node.value:
            # Ищем в левом поддереве (там хранятся меньшие значения)
            return self._search(node.left, value)
        else:
            # Ищем в правом поддереве (там хранятся большие значения)
            return self._search(node.right, value)

    # Нахождение узла с максимальным значением в поддереве
    # (Нужно для удаления узла с двумя детьми)
    def _find_max(self, node: TreeNode) -> TreeNode:
        # В BST максимальный элемент всегда самый правый
        while node and node.right:
            node = node.right  # Идем всегда вправо
        return node

    # Рекурсивное удаление узла из дерева
    def _delete_node(self, node: TreeNode, value: int) -> tuple[TreeNode, bool]:
        # Базовый случай: узел не найден
        if not node:
            return None, False  # Возвращаем None и False (не нашли)

        found = False  # Флаг, был ли найден и удален узел

        # Поиск удаляемого узла
        if value < node.value:  # Ищем в левом поддереве
            node.left, found = self._delete_node(node.left, value)
        elif value > node.value:  # Ищем в правом поддереве
            node.right, found = self._delete_node(node.right, value)
        else:  # Нашли узел для удаления (value == node.value)
            found = True

            # Случай 1: У узла нет левого потомка
            if not node.left:
                # Просто заменяем удаляемый узел на правого потомка
                return node.right, found

            # Случай 2: У узла нет правого потомка
            elif not node.right:
                # Просто заменяем удаляемый узел на левого потомка
                return node.left, found

            # Случай 3: У узла есть оба потомка
            else:
                # Находим максимальный элемент в левом поддереве
                # (или минимальный в правом - оба подходят)
                max_left = self._find_max(node.left)

                # Копируем значение максимального элемента в удаляемый узел
                node.value = max_left.value

                # Удаляем этот максимальный элемент из левого поддерева
                node.left, _ = self._delete_node(node.left, max_left.value)

        # Возвращаем текущий узел (возможно измененный) и флаг удаления
        return node, found

    # Рекурсивный вывод дерева в виде лесенки
    def _print_tree(self, node: TreeNode, level: int) -> None:
        if not node:  # Базовый случай: пустой узел
            return

        # Сначала выводим левое поддерево (меньшие значения)
        self._print_tree(node.left, level + 1)

        # Выводим текущий узел с отступом
        print("." * level + str(node.value))

        # Затем выводим правое поддерево (большие значения)
        self._print_tree(node.right, level + 1)

    # Публичный метод добавления
    def add(self, value: int) -> str:
        self.root, already_exists = self._add(self.root, value)
        return "ALREADY" if already_exists else "DONE"

    # Публичный метод удаления
    def delete(self, value: int) -> str:
        self.root, found = self._delete_node(self.root, value)
        return "DONE" if found else "CANNOT"

    # Публичный метод поиска
    def search(self, value: int) -> str:
        return "YES" if self._search(self.root, value) else "NO"

    # Публичный метод вывода дерева
    def print_tree(self) -> None:
        self._print_tree(self.root, 0)  # Начинаем с корня и нулевого уровня


# === ОСНОВНАЯ ПРОГРАММА ===
tree = BinarySearchTree()

# Чтение команд из стандартного ввода
for line in sys.stdin:
    parts = line.strip().split()  # Разбиваем строку на части
    if not parts:  # Пропускаем пустые строки
        continue

    command = parts[0]  # Первое слово - команда

    if command == "ADD":
        value = int(parts[1])  # Второе слово - значение
        print(tree.add(value))  # Добавляем и выводим результат

    elif command == "DELETE":
        value = int(parts[1])
        print(tree.delete(value))  # Удаляем и выводим результат

    elif command == "SEARCH":
        value = int(parts[1])
        print(tree.search(value))  # Ищем и выводим результат

    elif command == "PRINTTREE":
        tree.print_tree()  # Выводим дерево в виде лесенки