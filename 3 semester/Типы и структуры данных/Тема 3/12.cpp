#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canFormTeams(const vector<int>& heights, int n, int r, int c, int maxDiff) {
    int teamsFormed = 0;
    int i = 0;
    
    while (i <= n - c) {
        if (heights[i + c - 1] - heights[i] <= maxDiff) {
            teamsFormed++;
            i += c;
        } else {
            i++;
        }
    }
    
    return teamsFormed >= r;
}

int main() {
    int n, r, c;
    cin >> n >> r >> c;
    
    vector<int> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }
    
    sort(heights.begin(), heights.end());
    
    int left = 0;
    int right = heights[n - 1] - heights[0];
    int answer = right;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canFormTeams(heights, n, r, c, mid)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    cout << answer << endl;
    
    return 0;
}
