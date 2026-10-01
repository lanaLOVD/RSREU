class MaxHeap:
    def __init__(self):
        self.heap = []  # Массив для хранения элементов кучи

    # Просеивание элемента вверх для восстановления свойств кучи
    def sift_up(self, i):
        while i > 0:  # Пока не дошли до корня
            parent = (i - 1) // 2  # Индекс родительского элемента
            if self.heap[parent] >= self.heap[i]:
                break  # Свойство кучи восстановлено
            # Меняем местами с родителем, если родитель меньше
            self.heap[parent], self.heap[i] = self.heap[i], self.heap[parent]
            i = parent  # Переходим к родительской позиции

    # Просеивание элемента вниз для восстановления свойств кучи
    def sift_down(self, i):
        n = len(self.heap)
        while True:
            left = 2*i + 1  # Индекс левого потомка
            right = 2*i + 2  # Индекс правого потомка
            largest = i  # Предполагаем, что текущий элемент наибольший

            # Сравниваем с левым потомком
            if left < n and self.heap[left] > self.heap[largest]:
                largest = left
            # Сравниваем с правым потомком
            if right < n and self.heap[right] > self.heap[largest]:
                largest = right

            if largest == i:
                break  # Свойство кучи восстановлено

            # Меняем местами с наибольшим потомком
            self.heap[i], self.heap[largest] = self.heap[largest], self.heap[i]
            i = largest  # Переходим к позиции потомка

    # Вставка нового элемента в кучу
    def insert(self, x):
        self.heap.append(x)  # Добавляем в конец массива
        self.sift_up(len(self.heap) - 1)  # Просеиваем вверх

    # Извлечение максимального элемента (корня кучи)
    def extract(self):
        maximum = self.heap[0]  # Максимальный элемент - корень
        last = self.heap.pop()  # Удаляем последний элемент
        if self.heap:  # Если куча не пуста после удаления
            self.heap[0] = last  # Перемещаем последний элемент в корень
            self.sift_down(0)  # Просеиваем новый корень вниз
        return maximum


# Основное решение задачи
n = int(input())  # Количество команд
h = MaxHeap()  # Создаем экземпляр максимальной кучи

for _ in range(n):
    command = input().split()
    if command[0] == '0':              # Команда вставки: "0 число"
        h.insert(int(command[1]))
    else:                              # Команда извлечения: "1"
        print(h.extract())