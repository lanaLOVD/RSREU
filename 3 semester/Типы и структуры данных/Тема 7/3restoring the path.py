N, S, F = map(int, input().split())
S -= 1  # чтобы индексация с 0
F -= 1

# читаем матрицу смежности
graph = []
for _ in range(N):
    row = list(map(int, input().split()))
    # заменяем -1 на "бесконечность"
    graph.append([float('inf') if x == -1 else x for x in row])

dist = [float('inf')] * N
dist[S] = 0
prev = [None] * N
visited = [False] * N

for _ in range(N):
    # выбираем непосещенную вершину с минимальным расстоянием
    u = -1
    min_dist = float('inf')
    for i in range(N):
        if not visited[i] and dist[i] < min_dist:
            min_dist = dist[i]
            u = i
    if u == -1:
        break
    visited[u] = True

    # обновляем соседей
    for v in range(N):
        if graph[u][v] != float('inf'):
            if dist[v] > dist[u] + graph[u][v]:
                dist[v] = dist[u] + graph[u][v]
                prev[v] = u

# восстанавливаем путь
if dist[F] == float('inf'):
    print(-1)
else:
    path = []
    cur = F
    while cur is not None:
        path.append(cur + 1)  # возвращаем исходную индексацию
        cur = prev[cur]
    path.reverse()
    print(*path)
