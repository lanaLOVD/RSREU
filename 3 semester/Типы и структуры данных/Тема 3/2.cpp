#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Возвращает значение элемента из массива, ближайшего к target
int find_closest(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    // Бинарный поиск
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            // Нашли точное совпадение
            return arr[mid];
        } else if (arr[mid] < target) {
            // Искомый элемент в правой половине
            left = mid + 1;
        } else {
            // Искомый элемент в левой половине
            right = mid - 1;
        }
    }
    
    
    if (right < 0) {
        // Ближайший - первый элемент
        return arr[left];
    }
    if (left >= arr.size()) {
        // Ближайший - последний элемент
        return arr[right];
    }
    
    // Сравниваем два кандидата: arr[right] и arr[left]
    int diff1 = abs(arr[right] - target);
    int diff2 = abs(arr[left] - target);
    
    // Выбираем ближайший элемент
    if (diff1 < diff2 || (diff1 == diff2 && arr[right] < arr[left])) {
        return arr[right];
    }
    return arr[left];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    // Чтение отсортированного массива
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    for (int i = 0; i < k; i++) {
        int query;
        cin >> query;
        // Для каждого запроса находим и выводим ближайший элемент
        cout << find_closest(arr, query) << '\n';
    }
    
    return 0;
}
