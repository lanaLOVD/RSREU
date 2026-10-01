#include <iostream>
#include <queue>
using namespace std;

struct SlidingWindow {
    deque<int> deq;

    void push_back(int addedElement) {
        while (!deq.empty() && deq.back() > addedElement) {
            deq.pop_back();
        }
        deq.push_back(addedElement);
    }

    void pop_front(int removedElement) {
        if (!deq.empty() && deq.front() == removedElement)
            deq.pop_front();
    }

    int get_min() const {
        return deq.front();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    queue<int> numbers;
    SlidingWindow window;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        numbers.emplace(x);
        window.push_back(x);

        if (i >= k) {
            cout << window.get_min() << '\n'; 
            window.pop_front(numbers.front());
            numbers.pop();
        }
    }
}
