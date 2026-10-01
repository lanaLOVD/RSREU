def main():
    n, m = map(int, input().split())

    # Инициализация матрицы расстояний
    INF = 10 ** 9
    dist = [[INF] * n for _ in range(n)]

    # Расстояние от вершины до самой себя = 0
    for i in range(n):
        dist[i][i] = 0

    # Чтение рёбер
    for _ in range(m):
        s, e, l = map(int, input().split())
        # Приводим к 0-индексации
        s -= 1
        e -= 1
        # Дороги двунаправленные, берем минимальную длину если есть несколько дорог
        if l < dist[s][e]:
            dist[s][e] = l
            dist[e][s] = l

    # Алгоритм Флойда-Уоршелла
    for k in range(n):
        for i in range(n):
            if dist[i][k] < INF:
                for j in range(n):
                    if dist[k][j] < INF and dist[i][k] + dist[k][j] < dist[i][j]:
                        dist[i][j] = dist[i][k] + dist[k][j]

    # Находим вершину с минимальным максимальным расстоянием
    min_max_dist = INF
    best_vertex = 0

    for i in range(n):
        max_dist = 0
        for j in range(n):
            if dist[i][j] > max_dist:
                max_dist = dist[i][j]

        if max_dist < min_max_dist:
            min_max_dist = max_dist
            best_vertex = i

    # Выводим номер вершины (в 1-индексации)
    print(best_vertex + 1)


if __name__ == "__main__":
    main()