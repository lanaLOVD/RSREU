#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const long long INF = 2009000999LL;

struct Edge {
    int to;
    int weight;
};

void dijkstra(int start, const vector<vector<Edge>>& graph, vector<long long>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    dist[start] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();

        if (current_dist > dist[u]) {
            continue;
        }

        for (const auto& edge : graph[u]) {
            long long new_dist = current_dist + edge.weight;
            if (new_dist < dist[edge.to]) {
                dist[edge.to] = new_dist;
                pq.emplace(new_dist, edge.to);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int NUM;
    cin >> NUM;

    for (int t = 0; t < NUM; ++t) {
        int N, M;
        cin >> N >> M;

        vector<vector<Edge>> graph(N);

        for (int i = 0; i < M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        int start;
        cin >> start;

        vector<long long> dist;
        dijkstra(start, graph, dist);

        for (int i = 0; i < N; ++i) {
            cout << dist[i] << (i == N - 1 ? "\n" : " ");
        }
    }

    return 0;
}