#include <iostream>
#include <vector>
#include <stack>

int main() {
    int n;
    std::cin >> n;
    std::vector<long long> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    std::vector<long long> prefix_sum(n + 1, 0);
    for (size_t i = 0; i < n; ++i) {
        prefix_sum[i + 1] = prefix_sum[i] + numbers[i];
    }

    std::vector<size_t> indMinLeft(n);
    std::vector<size_t> indMinRight(n);

    std::stack<size_t> minStackLeft;
    std::stack<size_t> minStackRight;

    for (int ind = 0; ind != n; ++ind) {
        while (!minStackLeft.empty() && numbers[minStackLeft.top()] >= numbers[ind]) {
            minStackLeft.pop();
        }
        if (minStackLeft.empty()) {
            indMinLeft[ind] = 0;
        }
        else {
            indMinLeft[ind] = minStackLeft.top() + 1;
        }
        minStackLeft.push(ind);
    }

    for (int ind = numbers.size() - 1; ind >= 0; --ind) {
        while (!minStackRight.empty() && numbers[minStackRight.top()] >= numbers[ind]) {
            minStackRight.pop();
        }
        if (minStackRight.empty()) {
            indMinRight[ind] = numbers.size() - 1;
        }
        else {
            indMinRight[ind] = minStackRight.top() - 1;
        }
        minStackRight.push(ind);
    }

    long long maxPeriod = -1;
    int l = 0, r = 0;

    for (int i = 0; i < n; ++i) {
        long long sum = prefix_sum[indMinRight[i] + 1] - prefix_sum[indMinLeft[i]];
        long long significance = sum * numbers[i];

        if (significance >= maxPeriod) {
            maxPeriod = significance;
            l = indMinLeft[i];
            r = indMinRight[i];
        }
    }

    std::cout << maxPeriod << "\n" << l + 1 << " " << r + 1 << "\n";
}
