#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

//Ввод чисел в контейнеры

void inputNumbers(std::vector<int>& numbers,
                  std::priority_queue<int>& pq)
{
    int value{};

    std::cout << "Введите числа (0 - конец):\n";

    while (true)
    {
        std::cin >> value;

        if (value == 0)
        {
            break;
        }

        numbers.push_back(value);
        pq.push(value);
    }
}

//Вывод исходных чисел
 
void printSourceNumbers(const std::vector<int>& numbers)
{
    std::cout << "\nИсходные числа:\n";

    for (const int& num : numbers)
    {
        std::cout << std::setw(6) << num;
    }

    std::cout << '\n';
}

//Вывод чисел по убыванию

void printSortedNumbers(std::priority_queue<int> pq)
{
    std::cout << "\nПо убыванию:\n";

    while (!pq.empty())
    {
        std::cout << std::setw(6) << pq.top();
        pq.pop();
    }

    std::cout << '\n';
}

int main()
{
    std::vector<int> numbers{};
    std::priority_queue<int> pq{};

    inputNumbers(numbers, pq);
    printSourceNumbers(numbers);
    printSortedNumbers(pq);

    return 0;
}
