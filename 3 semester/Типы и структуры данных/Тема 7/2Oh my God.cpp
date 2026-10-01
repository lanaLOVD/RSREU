#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Константа для представления "бесконечности" (очень большое число)
// Выбрано 2009000999, что меньше чем 2^31, но достаточно большое для большинства задач
const long long INF = 2009000999LL;

// Структура для представления ребра графа
struct Edge {
    int to;      // вершина, в которую ведет ребро
    int weight;  // вес ребра
};

// Реализация алгоритма Дейкстры для поиска кратчайших путей от стартовой вершины
void dijkstra(int start, const vector<vector<Edge>>& graph, vector<long long>& dist) {
    int n = graph.size();  // количество вершин в графе

    // Инициализация массива расстояний
    // Изначально все расстояния бесконечны
    dist.assign(n, INF);
    // Расстояние от стартовой вершины до самой себя равно 0
    dist[start] = 0;

    // Приоритетная очередь (min-heap) для хранения пар (расстояние, вершина)
    // Используем greater<> для того, чтобы минимальный элемент был на вершине
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    // Добавляем стартовую вершину
    pq.emplace(0, start);

    while (!pq.empty()) {
        // Извлекаем вершину с минимальным расстоянием
        auto [current_dist, u] = pq.top();
        pq.pop();

        // Если извлеченное расстояние больше текущего известного,
        // значит, это устаревшая запись, пропускаем ее
        if (current_dist > dist[u]) {
            continue;
        }

        // Рассматриваем всех соседей текущей вершины
        for (const auto& edge : graph[u]) {
            long long new_dist = current_dist + edge.weight;

            // Если найден более короткий путь до соседа
            if (new_dist < dist[edge.to]) {
                dist[edge.to] = new_dist;  // обновляем расстояние
                pq.emplace(new_dist, edge.to);  // добавляем в очередь
            }
        }
    }
}

int main() {
    // Оптимизация ввода/вывода для ускорения работы
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int NUM;  // количество тестовых случаев
    cin >> NUM;

    // Обрабатываем каждый тестовый случай
    for (int t = 0; t < NUM; ++t) {
        int N, M;  // N - количество вершин, M - количество ребер
        cin >> N >> M;

        // Создаем список смежности для графа
        // graph[i] содержит список ребер, исходящих из вершины i
        vector<vector<Edge>> graph(N);

        // Читаем информацию о ребрах
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;

            // Граф неориентированный, поэтому добавляем ребро в обе стороны
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        int start;  // стартовая вершина
        cin >> start;

        vector<long long> dist;  // вектор для хранения расстояний
        dijkstra(start, graph, dist);  // запускаем алгоритм Дейкстры

        // Выводим результат
        for (int i = 0; i < N; ++i) {
            // Выводим расстояние до каждой вершины
            // Для последней вершины добавляем перевод строки, для остальных - пробел
            cout << dist[i] << (i == N - 1 ? "\n" : " ");
        }
    }

    return 0;
}