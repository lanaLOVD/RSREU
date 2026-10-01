#include <iostream>
#include <stack>
#include <queue>
#include <string>

bool CanBeSorted(std::queue<int>& track1) {
    std::stack<int> deadEnd;
    std::deque<int> track2;
    while (!track1.empty()) {
        if (deadEnd.empty()) {
            deadEnd.push(track1.front());
            track1.pop();
        }
        else if (deadEnd.top() > track1.front()) {
            deadEnd.push(track1.front());
            track1.pop();
        }
        else {
            track2.push_back(deadEnd.top());
            deadEnd.pop();
        }
    }
    while (!track2.empty()) {
        deadEnd.push(track2.back());
        track2.pop_back();
    }
    track2.push_back(deadEnd.top());
    deadEnd.pop();
    while (!deadEnd.empty()) {
        if (track2.back() < deadEnd.top()) {
            track2.push_back(deadEnd.top());
            deadEnd.pop();
        }
        else {
            return false;
        }
    }
    return true;
}

int main() {
    int wagonsAmount;
    std::queue<int> train;

    std::cin >> wagonsAmount;

    for (int i = 0; i != wagonsAmount; ++i) {
        int wagonNumber;
        std::cin >> wagonNumber;
        train.push(wagonNumber);
    }

    if (CanBeSorted(train)) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
}
