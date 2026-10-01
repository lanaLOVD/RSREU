#include <iostream>
#include <vector>

int main() {
    int n;
    std::vector<int> numbers;

    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        numbers.push_back(i);
    }

    if (numbers.size() >= 3) {
        for (size_t i = 2; i != numbers.size(); ++i) {
            std::swap(numbers[i], numbers[i / 2]);
        }
    }

    for (int number : numbers) {
        std::cout << number << " ";
    }
}
