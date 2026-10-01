#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> pop = a;
    vector<long long> nextTime(n);
    for (int i = 0; i < n; i++) {
        nextTime[i] = max(1000 - a[i], 1);
    }

    long long t = 0;
    int pos = 0;

    while (true) {
        // Находим ближайшее событие вообще
        long long min_time = LLONG_MAX;
        int min_idx = -1;
        for (int i = 0; i < n; i++) {
            if (nextTime[i] < min_time) {
                min_time = nextTime[i];
                min_idx = i;
            }
        }

        if (min_idx == -1) break; // все события обработаны (маловероятно)

        // Проверяем, успеваем ли к этому событию
        if (t + abs(pos - min_idx) <= min_time) {
            // Успеваем
            t = max(t + abs(pos - min_idx), min_time);
            pos = min_idx;
            pop[min_idx]++;
            nextTime[min_idx] = t + max(1000 - pop[min_idx], 1);
        } else {
            // Не успеваем — ответ
            cout << t << endl;
            return 0;
        }
    }

    cout << t << endl;
    return 0;
}
