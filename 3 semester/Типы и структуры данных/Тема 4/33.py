import sys
import heapq  # Библиотека для работы с кучами (min-heap)

heap = []  # Куча будет использоваться как min-heap
results = []  # Список для хранения результатов

# Чтение ввода построчно
for line in sys.stdin:
    line = line.strip()  # Удаляем лишние пробелы
    if not line:
        continue  # Пропускаем пустые строки

    if line == "CLEAR":
        heap = []  # Очищаем кучу
    elif line.startswith("ADD"):
        _, n = line.split()  # Разделяем команду и число
        heapq.heappush(heap, int(n))  # Добавляем элемент в min-heap
    elif line == "EXTRACT":
        if heap:
            # Извлекаем минимальный элемент из min-heap
            results.append(str(heapq.heappop(heap)))
        else:
            results.append("CANNOT")  # Если куча пуста

# Выводим все результаты одной строкой
sys.stdout.write("\n".join(results))