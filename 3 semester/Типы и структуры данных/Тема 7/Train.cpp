#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int to;
    long long depart;
    long long arrive;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, E;
    cin >> N >> E;

    int M;
    cin >> M;

    vector<vector<Edge>> graph(N + 1);

    for (int i = 0; i < M; i++) {
        int K;
        cin >> K;

        vector<pair<int, long long>> stops(K);
        for (int j = 0; j < K; j++) {
            cin >> stops[j].first >> stops[j].second;
        }

        // Добавляем ребра между последовательными остановками
        for (int j = 0; j + 1 < K; j++) {
            int u = stops[j].first;
            int v = stops[j + 1].first;
            long long t1 = stops[j].second;
            long long t2 = stops[j + 1].second;

            graph[u].push_back({v, t1, t2});
        }
    }

    // Дейкстра по времени
    const long long INF = numeric_limits<long long>::max();
    vector<long long> dist(N + 1, INF);

    dist[1] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;

    pq.push({0, 1});

    while (!pq.empty()) {
        auto [curTime, u] = pq.top();
        pq.pop();

        if (curTime > dist[u]) continue;

        for (auto &e : graph[u]) {
            if (dist[u] <= e.depart) {
                if (dist[e.to] > e.arrive) {
                    dist[e.to] = e.arrive;
                    pq.push({dist[e.to], e.to});
                }
            }
        }
    }

    if (dist[E] == INF) cout << -1 << "\n";
    else cout << dist[E] << "\n";

    return 0;
}
