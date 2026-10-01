#include <iostream>
#include <vector>

int main() {
    int n;

    std::cin >> n;

    std::vector<int> answers(n);

    for (int i = 0; i != n; ++i) {
        int k;

        std::cin >> k;

        std::vector<float> input;

        for (int j = 0; j != k; ++j) {
            float priority;
            std::cin >> priority;
            input.push_back(priority);
        }

        bool cannotBeSorted = false;

        for (size_t i = 0; i != input.size() - 2; ++i) {
            if ((input[i] < input[i + 1]) && (input[i + 2] < input[i])) {
                cannotBeSorted = true;
                break;
            }
        }

        if (cannotBeSorted) {
            std::cout << "0\n";
        }
        else {
            std::cout << "1\n";
        }
    }
}
