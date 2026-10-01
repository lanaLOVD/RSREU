curr_sum = 0
distances = sorted(list(map(int, input().split())))
prices = sorted(list(map(int, input().split())), reverse=True)
for i in range(len(prices)):
    curr_sum += distances[i] * prices[i]
print(curr_sum)