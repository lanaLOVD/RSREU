#include <iostream>
#include <list>
#include <string>

struct Stack {
    std::list<int> stc;

    void PushFront(int& x) {
        stc.push_front(x);
    }

    void PushBack(int& x) {
        stc.push_back(x);
    }

    void PopFront() {
        stc.pop_front();
    }

    void PopBack() {
        stc.pop_back();
    }

    int Front() {
        return stc.front();
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
        else if (command == "push_front") {
            int n;
            std::cin >> n;
            numbersStack.PushFront(n);
            std::cout << "ok\n";
        }
        else if (command == "push_back") {
            int n;
            std::cin >> n;
            numbersStack.PushBack(n);
            std::cout << "ok\n";
        }
        else if (command == "pop_front") {
            if (numbersStack.IsEmpty()) {
                std::cout << "error\n";
                continue;
            }
            std::cout << numbersStack.Front() << "\n";
            numbersStack.PopFront();
        }
        else if (command == "pop_back") {
            if (numbersStack.IsEmpty()) {
                std::cout << "error\n";
                continue;
            }
            std::cout << numbersStack.Back() << "\n";
            numbersStack.PopBack();
        }
        else if (command == "front") {
            if (numbersStack.IsEmpty()) {
                std::cout << "error\n";
                continue;
            }
            std::cout << numbersStack.Front() << "\n";
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
