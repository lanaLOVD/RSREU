class MaxHeap:
    def __init__(self):
        self.heap = []

    # Просевание вверх
    def sift_up(self, i):
        while i > 0:
            parent = (i - 1) // 2
            if self.heap[parent] >= self.heap[i]:
                break
            self.heap[parent], self.heap[i] = self.heap[i], self.heap[parent]
            i = parent

    # Просевание вниз
    def sift_down(self, i):
        n = len(self.heap)
        while True:
            left = 2*i + 1
            right = 2*i + 2
            largest = i

            if left < n and self.heap[left] > self.heap[largest]:
                largest = left
            if right < n and self.heap[right] > self.heap[largest]:
                largest = right

            if largest == i:
                break

            self.heap[i], self.heap[largest] = self.heap[largest], self.heap[i]
            i = largest

    # Вставка
    def insert(self, x):
        self.heap.append(x)
        self.sift_up(len(self.heap) - 1)

    # Извлечение максимума
    def extract(self):
        maximum = self.heap[0]
        last = self.heap.pop()
        if self.heap:
            self.heap[0] = last
            self.sift_down(0)
        return maximum


# Основное решение задачи
n = int(input())
h = MaxHeap()

for _ in range(n):
    command = input().split()
    if command[0] == '0':              # Insert
        h.insert(int(command[1]))
    else:                              # Extract
        print(h.extract())
