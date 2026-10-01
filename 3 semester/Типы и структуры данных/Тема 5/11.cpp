
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    set<int> s;
    char operation;
    int value;
    long long last_answer = 0; // храним последний ответ на запрос
    bool prev_was_query = false; // был ли предыдущий операцией запроса
    
    for (int i = 0; i < n; i++) {
        cin >> operation >> value;
        
        if (operation == '+') {
            if (prev_was_query) {
                // Если предыдущая операция была запросом, добавляем (value + last_answer) % 10^9
                value = (value + last_answer) % 1000000000;
            }
            s.insert(value);
            prev_was_query = false;
        } else { // operation == '?'
            auto it = s.lower_bound(value);
            if (it == s.end()) {
                last_answer = -1;
            } else {
                last_answer = *it;
            }
            cout << last_answer << "\n";
            prev_was_query = true;
        }
    }
    
    return 0;
}
