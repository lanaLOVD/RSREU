#include <string>
#include <vector>
#include <iostream>
#include <stack>

bool Correct(const std::string& str) {
    std::stack<char> brackets;

    for (size_t i = 0; i != str.size(); ++i) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            brackets.push(str[i]);
        }
        else {
            if (brackets.empty()) {
                return false;
            }
            if ((str[i] == ')' && brackets.top() == '(') || (str[i] == '}' && brackets.top() == '{') ||
                (str[i] == ']' && brackets.top() == '[')) {
                brackets.pop();
            }
            else {
                return false;
            }
        }
    }

    return brackets.empty();
}

int main() {
    std::string str;
    std::cin >> str;
    if (Correct(str)) {
        std::cout << "yes";
    }
    else {
        std::cout << "no";
    }
}
