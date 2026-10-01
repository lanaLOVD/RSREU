#include <string>
#include <iostream>
#include <stack>

int main() {
    std::stack<int> numbers;
    std::string input;


    while (std::cin >> input) {
        if (input == "+") {
            int op1 = numbers.top();
            numbers.pop();
            int op2 = numbers.top();
            numbers.pop();
            numbers.push(op1 + op2);
        }
        else if (input == "-") {
            int op1 = numbers.top();
            numbers.pop();
            int op2 = numbers.top();
            numbers.pop();
            numbers.push(op2 - op1);
        }
        else if (input == "*") {
            int op1 = numbers.top();
            numbers.pop();
            int op2 = numbers.top();
            numbers.pop();
            numbers.push(op2 * op1);
        }
        else {
            numbers.push(std::stoi(input));
        }
    }
    std::cout << numbers.top();
}
