import sys
import heapq

heap = []
results = []

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue

    if line == "CLEAR":
        heap = []
    elif line.startswith("ADD"):
        _, n = line.split()
        heapq.heappush(heap, int(n))
    elif line == "EXTRACT":
        if heap:
            results.append(str(heapq.heappop(heap)))
        else:
            results.append("CANNOT")

sys.stdout.write("\n".join(results))
