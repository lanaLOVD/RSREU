import sys
import heapq


def solve():
    data = sys.stdin.read().strip().split()
    if not data:
        return

    n = int(data[0])
    numbers = list(map(int, data[1:1 + n]))

    # Создаем min-кучу
    heap = numbers.copy()
    heapq.heapify(heap)

    total_cost = 0.0

    # Пока в куче больше одного элемента
    while len(heap) > 1:
        # Извлекаем два минимальных числа
        a = heapq.heappop(heap)
        b = heapq.heappop(heap)

        # Суммируем их
        s = a + b

        # Добавляем стоимость операции (5% от суммы)
        total_cost += s * 0.05

        # Помещаем сумму обратно в кучу
        heapq.heappush(heap, s)

    # Выводим результат с двумя знаками после запятой
    print(f"{total_cost:.2f}")


if __name__ == "__main__":
    solve()