import sys

class Node:
    # Оптимизация памяти: заранее объявляем атрибуты
    __slots__ = ('value', 'left', 'right')

    def __init__(self, value):
        self.value = value  # Значение узла
        self.left = None    # Левый потомок (меньшие значения)
        self.right = None   # Правый потомок (большие значения)

def main():
    # Чтение всех данных
    data = sys.stdin.read().strip().split()

    # Если нет данных или первый элемент 0
    if not data or data[0] == '0':
        return  # Ничего не выводим

    # Построение бинарного дерева поиска (BST)
    root = None  # Корень дерева

    for s in data:
        num = int(s)
        if num == 0:  # 0 - признак конца ввода
            break

        # Если дерево пустое
        if root is None:
            root = Node(num)  # Создаем корень
            continue

        # Вставка нового узла в BST
        curr = root
        while True:
            if num == curr.value:  # Элемент уже есть
                break  # Игнорируем дубликаты
            elif num < curr.value:  # Идем в левое поддерево
                if curr.left is None:  # Нашли место для вставки
                    curr.left = Node(num)
                    break
                curr = curr.left  # Продолжаем поиск влево
            else:  # Идем в правое поддерево
                if curr.right is None:  # Нашли место для вставки
                    curr.right = Node(num)
                    break
                curr = curr.right  # Продолжаем поиск вправо

    # Итеративный ин-ордер обход (in-order traversal)
    # Выводит элементы в отсортированном порядке
    result = []  # Список для хранения результатов
    stack = []   # Стек для обхода
    curr = root  # Начинаем с корня

    while stack or curr:
        # Идем до самого левого узла (наименьшего значения)
        while curr:
            stack.append(curr)  # Запоминаем узел в стеке
            curr = curr.left    # Идем влево

        # Извлекаем узел из стека
        curr = stack.pop()
        result.append(curr.value)  # Добавляем значение в результат

        # Переходим к правому поддереву
        curr = curr.right

    # Вывод результатов (каждое значение на новой строке)
    sys.stdout.write("\n".join(map(str, result)) + "\n")

if __name__ == "__main__":
    main()