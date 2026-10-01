#include <iostream>
#include <vector>
#include <string>

struct Balloons {
    std::vector<int> balloonsStack;

    int Push(int& x) {
        int poped = 0;
        if (!balloonsStack.empty()) {
            if (x != balloonsStack.back() && HasChainOfThree()) {
                poped = PopSameLast();
            }
        }
        balloonsStack.push_back(x);
        return poped;
    }

    int PopSameLast() {
        int poped = 0;
        int i = balloonsStack.size() - 1;
        int key = balloonsStack.back();
        while (i >= 0 && balloonsStack[i] == key) {
            balloonsStack.pop_back();
            ++poped;
            --i;
        }
        return poped;
    }

    bool HasChainOfThree() {
        if (balloonsStack.size() < 3) {
            return false;
        }
        return ((balloonsStack[balloonsStack.size() - 1] == balloonsStack[balloonsStack.size() - 2]) &&
            (balloonsStack[balloonsStack.size() - 2] == balloonsStack[balloonsStack.size() - 3]));
    }
};


int main() {
    int balloonsAmount;
    int destroyedBalloons = 0;
    Balloons balloons;

    std::cin >> balloonsAmount;

    for (int i = 0; i != balloonsAmount; ++i) {
        int balloonColor;
        std::cin >> balloonColor;
        destroyedBalloons += balloons.Push(balloonColor);
    }
    if (balloons.HasChainOfThree()) {
        destroyedBalloons += balloons.PopSameLast();
    }
    std::cout << destroyedBalloons;
}
