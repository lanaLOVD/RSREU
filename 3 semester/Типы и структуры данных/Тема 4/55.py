import sys
import heapq


def solve():
    data = sys.stdin.read().strip().split()  # Чтение всех данных
    if not data:
        return  # Пустой ввод

    n = int(data[0])  # Количество чисел
    numbers = list(map(int, data[1:1 + n]))  # Список чисел

    # Создаем min-heap из всех чисел
    heap = numbers.copy()
    heapq.heapify(heap)  # Преобразуем список в min-heap за O(n)

    total_cost = 0.0  # Общая стоимость операций

    # Пока в куче больше одного элемента
    while len(heap) > 1:
        # Извлекаем два минимальных числа
        a = heapq.heappop(heap)  # Первое минимальное
        b = heapq.heappop(heap)  # Второе минимальное

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