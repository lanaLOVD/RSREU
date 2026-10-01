import sys


def solve_with_custom_heap():
    heap = []  # Массив для хранения кучи (max-heap)
    results = []  # Список для результатов

    def _sift_up(idx):
        """Просеивание элемента вверх в max-heap."""
        while idx > 0:
            parent = (idx - 1) >> 1  # Быстрый способ вычисления (idx-1)//2
            if heap[idx] <= heap[parent]:
                break  # Свойство кучи восстановлено
            # Меняем местами с родителем
            heap[idx], heap[parent] = heap[parent], heap[idx]
            idx = parent  # Переходим к родительской позиции

    def _sift_down(idx):
        """Просеивание элемента вниз в max-heap."""
        n = len(heap)
        while True:
            left = (idx << 1) + 1  # Быстрый способ: 2*idx + 1
            right = left + 1  # 2*idx + 2
            largest = idx  # Предполагаем, что текущий элемент наибольший

            if left < n and heap[left] > heap[largest]:
                largest = left
            if right < n and heap[right] > heap[largest]:
                largest = right

            if largest == idx:
                break  # Свойство кучи восстановлено

            # Меняем местами с наибольшим потомком
            heap[idx], heap[largest] = heap[largest], heap[idx]
            idx = largest

    # Обработка команд построчно
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue

        if line == "CLEAR":
            heap.clear()  # Очищаем кучу
        elif line.startswith("ADD"):
            n = int(line.split()[1])  # Извлекаем число для добавления
            heap.append(n)  # Добавляем в конец
            _sift_up(len(heap) - 1)  # Просеиваем вверх
        elif line == "EXTRACT":
            if not heap:
                results.append("CANNOT")  # Куча пуста
            else:
                # Меняем местами корень (максимум) с последним элементом
                heap[0], heap[-1] = heap[-1], heap[0]
                # Извлекаем максимальный элемент
                max_val = heap.pop()
                if heap:
                    _sift_down(0)  # Восстанавливаем свойства кучи
                results.append(str(max_val))

    sys.stdout.write("\n".join(results))  # Выводим результаты


if __name__ == "__main__":
    solve_with_custom_heap()