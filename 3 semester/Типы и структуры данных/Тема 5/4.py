import sys


def main():
    data = sys.stdin.read().strip().split()
    nums = []

    for s in data:
        num = int(s)
        if num == 0:
            break
        nums.append(num)

    if len(nums) < 2:
        print(0)
        return

    # Убираем дубликаты
    unique = sorted(set(nums), reverse=True)
    print(unique[1])


if __name__ == "__main__":
    main()