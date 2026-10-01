#include <iostream>
#include <vector>
#include <stack>

int main() {
    int n;
    std::cin >> n;

    std::stack<std::pair<long long, long long>> rectangles;

    rectangles.push({ 0, -1 });

    long long maxArea = 0;

    for (int ind = 1; ind <= n + 1; ++ind) {
        long long h;
        long long x = ind;
        if (ind == n + 1) {
            h = 0;
        }
        else {
            std::cin >> h;
        }
        while (h <= rectangles.top().second) {
            x = rectangles.top().first;
            long long area = rectangles.top().second * (ind - rectangles.top().first);
            rectangles.pop();
            if (area > maxArea) {
                maxArea = area;
            }
        }
        rectangles.push({ x, h });
    }

    std::cout << maxArea;
}
