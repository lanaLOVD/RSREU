#include <iostream>
#include <algorithm>
using namespace std;

bool canMakeCopies(int time, int N, int x, int y) {
    return (time / x) + (time / y) >= N - 1;
}

int main() {
    int N, x, y;
    cin >> N >> x >> y;
    
    if (x > y) swap(x, y);
    
    int left = 0;
    int right = N * y;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (canMakeCopies(mid, N, x, y)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    cout << left + x << endl;
    
    return 0;
}
