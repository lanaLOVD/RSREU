import sys
import heapq


def max_time_until_miss(n, populations):
    """
    Вычисляет максимальное время, которое Игорь может записывать рождения рыбок
    без пропусков.
    
    n - количество аквариумов
    populations - начальные популяции в каждом аквариуме
    """

    # Функция для вычисления времени до следующей рыбки
    def next_birth_time(current_pop):
        # Время ожидания зависит от текущей популяции
        wait = max(1000 - current_pop, 1)  # Минимум 1 секунда
        return current_pop + 1, wait  # Новая популяция и время ожидания

    # Инициализируем события для каждого аквариума
    events = []  # Куча событий (min-heap по времени)

    for i in range(n):
        pop = populations[i]  # Начальная популяция
        next_pop, wait = next_birth_time(pop)  # Вычисляем следующее событие
        # (время рождения, номер аквариума, новая популяция)
        heapq.heappush(events, (wait, i, next_pop))

    # Начальные условия: Игорь у первого аквариума в момент времени 0
    igor_position = 0  # Позиция Игоря (номер аквариума)
    current_time = 0  # Текущее время

    while True:
        # Получаем ближайшее событие (рождение рыбки)
        birth_time, aquarium, new_pop = heapq.heappop(events)

        # Время, когда Игорь освободится (если он не у нужного аквариума)
        travel_time = abs(igor_position - aquarium)  # Время перемещения
        igor_available_time = current_time + travel_time

        # Если Игорь не успевает к рождению
        if igor_available_time > birth_time:
            return birth_time  # Возвращаем время первого пропуска

        # Игорь успевает, обновляем состояние
        current_time = birth_time  # Игорь записывает рождение
        igor_position = aquarium  # Перемещается к аквариуму

        # Генерируем следующее событие для этого аквариума
        next_pop, wait = next_birth_time(new_pop)
        next_birth = birth_time + wait
        heapq.heappush(events, (next_birth, aquarium, next_pop))


def solve():
    data = sys.stdin.read().strip().split()  # Чтение всех данных
    if not data:
        return

    n = int(data[0])  # Количество аквариумов
    populations = []  # Список начальных популяций

    for i in range(1, n + 1):
        populations.append(int(data[i]))

    result = max_time_until_miss(n, populations)
    print(result)


if __name__ == "__main__":
    solve()