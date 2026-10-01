N = int(input())
adj = [list(map(int, input().split())) for _ in range(N)]

for k in range(N):
    for i in range(N):
        for j in range(N):
            if adj[i][k] and adj[k][j]:
                adj[i][j] = 1

for row in adj:
    print(*row)
