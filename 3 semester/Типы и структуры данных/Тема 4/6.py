import sys


def solve():
    data = sys.stdin.read().strip().split()
    if not data:
        print(0)
        return

    n = int(data[0])
    if n == 0:
        print(0)
        return

    events = []

    # Читаем все грузы и создаем события
    for i in range(n):
        t = int(data[2 * i + 1])
        l = int(data[2 * i + 2])
        # Событие начала: +1 в момент t
        events.append((t, 1))
        # Событие окончания: -1 в момент t + l
        events.append((t + l, -1))

    # Сортируем события:
    # 1. По времени
    # 2. При равенстве времени: сначала окончания (-1), потом начала (+1)
    events.sort(key=lambda x: (x[0], x[1]))

    current = 0
    max_count = 0

    for time, event_type in events:
        current += event_type
        if current > max_count:
            max_count = current

    print(max_count)


if __name__ == "__main__":
    solve()