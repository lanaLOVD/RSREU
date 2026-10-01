import sys
import heapq

input = sys.stdin.readline

N = int(input())
d, v = map(int, input().split())
d -= 1
v -= 1

R = int(input())
flights = [[] for _ in range(N)]
for _ in range(R):
    u, t_dep, w, t_arr = map(int, input().split())
    flights[u - 1].append((t_dep, w - 1, t_arr))  # (время отправления, город назначения, время прибытия)

INF = 10**9
arrival_time = [INF] * N
arrival_time[d] = 0

heap = [(0, d)]  # (время прибытия, город)

while heap:
    cur_time, city = heapq.heappop(heap)
    if cur_time > arrival_time[city]:
        continue
    for t_dep, dest, t_arr in flights[city]:
        if cur_time <= t_dep and arrival_time[dest] > t_arr:
            arrival_time[dest] = t_arr
            heapq.heappush(heap, (t_arr, dest))

print(arrival_time[v] if arrival_time[v] != INF else -1)
