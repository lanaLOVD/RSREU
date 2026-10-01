import sys


def solve_with_custom_heap():
    heap = []
    results = []

    def _sift_up(idx):
        while idx > 0:
            parent = (idx - 1) >> 1  # быстрее чем //
            if heap[idx] <= heap[parent]:
                break
            heap[idx], heap[parent] = heap[parent], heap[idx]
            idx = parent

    def _sift_down(idx):
        n = len(heap)
        while True:
            left = (idx << 1) + 1  # 2*idx + 1
            right = left + 1
            largest = idx

            if left < n and heap[left] > heap[largest]:
                largest = left
            if right < n and heap[right] > heap[largest]:
                largest = right

            if largest == idx:
                break

            heap[idx], heap[largest] = heap[largest], heap[idx]
            idx = largest

    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue

        if line == "CLEAR":
            heap.clear()  # O(1)
        elif line.startswith("ADD"):
            n = int(line.split()[1])
            heap.append(n)
            _sift_up(len(heap) - 1)
        elif line == "EXTRACT":
            if not heap:
                results.append("CANNOT")
            else:
                # Без явного присваивания, сразу обмен
                heap[0], heap[-1] = heap[-1], heap[0]
                max_val = heap.pop()
                if heap:
                    _sift_down(0)
                results.append(str(max_val))

    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    solve_with_custom_heap()