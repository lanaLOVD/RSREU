#include <iostream>
#include <vector>

using namespace std;


inline bool binarySearch(const int* arr, int n, int target) {
    int left = 0;
    int right = n - 1;
    
    // Классический бинарный поиск
    while (left <= right) {
        
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            // Нашли элемент
            return true;
        } else if (arr[mid] < target) {
            // Искомый элемент в правой половине
            left = mid + 1;
        } else {
            // Искомый элемент в левой половине
            right = mid - 1;
        }
    }
    
    // Элемент не найден
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    // Первый массив (отсортированный, по условию задачи)
    vector<int> first_array(n);
    for (int i = 0; i < n; ++i) {
        cin >> first_array[i];
    }
    
    int num; // Число для поиска
    for (int i = 0; i < k; ++i) {
        cin >> num;
        // Прямой вывод результата поиска
        if (binarySearch(first_array.data(), n, num)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
