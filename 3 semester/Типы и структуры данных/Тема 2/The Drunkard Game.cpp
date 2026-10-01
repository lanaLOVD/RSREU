#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

int main() {
    int cards = 5;

    std::deque<int> firstHand;
    std::deque<int> secondHand;

    for (int i = 0; i < cards; ++i) {
        int seniority;
        std::cin >> seniority;
        firstHand.push_back(seniority);
    }

    for (int i = 0; i < cards; ++i) {
        int seniority;
        std::cin >> seniority;
        secondHand.push_back(seniority);
    }

    double moveNumber = 0;

    while (!firstHand.empty() && !secondHand.empty() && moveNumber < std::pow(10, 6)) {
        int firstCard = firstHand.front();
        int secondCard = secondHand.front();
        firstHand.pop_front();
        secondHand.pop_front();
        if (firstCard == 0 && secondCard == 9) {
            firstHand.push_back(firstCard);
            firstHand.push_back(secondCard);
        }
        else if (secondCard == 0 && firstCard == 9) {
            secondHand.push_back(firstCard);
            secondHand.push_back(secondCard);
        }
        else if (firstCard > secondCard) {
            firstHand.push_back(firstCard);
            firstHand.push_back(secondCard);
        }
        else if (secondCard > firstCard) {
            secondHand.push_back(firstCard);
            secondHand.push_back(secondCard);
        }
        ++moveNumber;
    }

    if (firstHand.empty()) {
        std::cout << "second " << moveNumber;
    }
    else if (secondHand.empty()) {
        std::cout << "first " << moveNumber;
    }
    else {
        std::cout << "botva";
    }
}
