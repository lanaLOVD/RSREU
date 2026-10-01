INF = 10**9

N, s, t = map(int, input().split())
s -= 1  # индексация с 0
t -= 1

dist = []
for _ in range(N):
    row = list(map(int, input().split()))
    dist_row = []
    for x in row:
        if x == -1:
            dist_row.append(INF)
        else:
            dist_row.append(x)
    dist.append(dist_row)

# Алгоритм Флойда–Уоршелла
for k in range(N):
    for i in range(N):
        for j in range(N):
            if dist[i][k] + dist[k][j] < dist[i][j]:
                dist[i][j] = dist[i][k] + dist[k][j]

print(dist[s][t] if dist[s][t] != INF else -1)
