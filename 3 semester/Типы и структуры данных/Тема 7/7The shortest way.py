INF = 10**18

N = int(input())
dist = []
for _ in range(N):
    row = list(map(int, input().split()))
    dist.append(row[:])  # граф полный, поэтому все веса есть

# Алгоритм Флойда–Уоршелла
for k in range(N):
    for i in range(N):
        for j in range(N):
            if dist[i][k] + dist[k][j] < dist[i][j]:
                dist[i][j] = dist[i][k] + dist[k][j]

# Проверка на отрицательные циклы
negative_cycle = any(dist[i][i] < 0 for i in range(N))
if negative_cycle:
    print(-1)
else:
    # ищем минимальный путь между разными вершинами
    ans = INF
    for i in range(N):
        for j in range(N):
            if i != j:
                ans = min(ans, dist[i][j])
    print(ans)
