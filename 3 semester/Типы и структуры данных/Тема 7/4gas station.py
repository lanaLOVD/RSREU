import sys
import heapq

input = sys.stdin.readline

N = int(input())
price = list(map(int, input().split()))
M = int(input())

graph = [[] for _ in range(N)]
for _ in range(M):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    graph[u].append(v)
    graph[v].append(u)  # дороги двухсторонние

INF = 10**9
dist = [INF] * N
dist[0] = 0  # стартовый город

heap = [(0, 0)]  # (стоимость, вершина)

while heap:
    cost, u = heapq.heappop(heap)
    if cost > dist[u]:
        continue
    for v in graph[u]:
        new_cost = cost + price[u]
        if new_cost < dist[v]:
            dist[v] = new_cost
            heapq.heappush(heap, (new_cost, v))

print(dist[N-1] if dist[N-1] != INF else -1)
