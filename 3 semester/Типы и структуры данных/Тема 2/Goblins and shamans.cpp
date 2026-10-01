#include <iostream>
#include <deque>

struct GoblinsQueue {
    std::deque<int> firstHalf;
    std::deque<int> secondHalf;

    void Push(int x) {
        secondHalf.push_back(x);
        Balance();
    }

    void PushSenior(int x) {
        firstHalf.push_back(x);
        Balance();
    }

    int GetFirst() {
        return firstHalf.front();
    }

    void PopFirst() {
        firstHalf.pop_front();
        Balance();
    }

    void Balance() {
        if (firstHalf.size() < secondHalf.size()) {
            firstHalf.push_back(secondHalf.front());
            secondHalf.pop_front();
        }
        else if (firstHalf.size() > secondHalf.size() + 1) {
            secondHalf.push_front(firstHalf.back());
            firstHalf.pop_back();
        }
    }
};

int main() {
    int n;
    int x;
    char command;

    GoblinsQueue goblins;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> command;
        if (command == '+') {
            std::cin >> x;
            goblins.Push(x);
        }
        else if (command == '*') {
            std::cin >> x;
            goblins.PushSenior(x);
        }
        else if (command == '-') {
            std::cout << goblins.GetFirst() << "\n";
            goblins.PopFirst();
        }
    }
}
