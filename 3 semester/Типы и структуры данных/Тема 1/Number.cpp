#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::string input;
    std::vector<std::string> inputStrings;

    while (std::cin >> input) {
        inputStrings.push_back(input);
    }

    std::sort(inputStrings.begin(), inputStrings.end(), [](const std::string& lhs_str, const std::string& rhs_str) {
        return lhs_str + rhs_str > rhs_str + lhs_str;
        });

    for (std::string str : inputStrings) {
        std::cout << str;
    }
}
