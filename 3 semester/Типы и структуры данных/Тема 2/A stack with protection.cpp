#include <iostream>
#include <vector>
#include <string>

struct Stack {
    std::vector<int> stc;

    void Push(int& x) {
        stc.push_back(x);
    }

    void Pop() {
        stc.pop_back();
    }

    int Back() {
        return stc.back();
    }

    size_t Size() {
        return stc.size();
    }

    void Clear() {
        return stc.clear();
    }

    bool IsEmpty() {
        return stc.empty();
    }
};

int main() {
    std::string command;

    Stack numbersStack;

    while (true) {
        std::cin >> command;
        if (command == "exit") {
            std::cout << "bye";
            break;
        }
        else if (command == "push") {
            int n;
            std::cin >> n;
            numbersStack.Push(n);
            std::cout << "ok\n";
        }
        else if (command == "pop") {
            if (numbersStack.IsEmpty()) {
                std::cout << "error\n";
                continue;
            }
            std::cout << numbersStack.Back() << "\n";
            numbersStack.Pop();
        }
        else if (command == "back") {
            if (numbersStack.IsEmpty()) {
                std::cout << "error\n";
                continue;
            }
            std::cout << numbersStack.Back() << "\n";
        }
        else if (command == "size") {
            std::cout << numbersStack.Size() << "\n";
        }
        else if (command == "clear") {
            numbersStack.Clear();
            std::cout << "ok\n";
        }
    }
}
