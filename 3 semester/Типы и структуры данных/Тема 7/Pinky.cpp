#include <iostream>
#include <vector>
#include <limits>

using namespace std;

using ll = long long;
const ll NEG_INF = (ll)-9e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<ll>> dist(n, vector<ll>(n, NEG_INF));
    vector<vector<int>> nextv(n, vector<int>(n, -1));
    vector<vector<int>> edgeId(n, vector<int>(n, -1));

    // dist[v][v] = 0
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        nextv[i][i] = i;
    }

    // Read edges
    for (int id = 1; id <= m; ++id) {
        int b, e;
        ll w;
        cin >> b >> e >> w;
        b--, e--;

        if (w > dist[b][e]) {
            dist[b][e] = w;
            nextv[b][e] = e;
            edgeId[b][e] = id;
        }
    }

    // Read concerts
    vector<int> concerts(k);
    for (int i = 0; i < k; ++i) {
        cin >> concerts[i];
        concerts[i]--;
    }

    // Floyd–Warshall for maximum path
    for (int mid = 0; mid < n; ++mid) {
        for (int i = 0; i < n; ++i) {
            if (dist[i][mid] == NEG_INF) continue;
            for (int j = 0; j < n; ++j) {
                if (dist[mid][j] == NEG_INF) continue;

                ll val = dist[i][mid] + dist[mid][j];
                if (val > dist[i][j]) {
                    dist[i][j] = val;
                    nextv[i][j] = nextv[i][mid];
                }
            }
        }
    }

    // Detect positive cycles
    vector<int> posCycle;
    for (int c = 0; c < n; ++c) {
        if (dist[c][c] > 0) posCycle.push_back(c);
    }

    // Check if infinitely kind for any segment
    for (int t = 0; t + 1 < k; ++t) {
        int a = concerts[t];
        int b = concerts[t + 1];

        for (int c : posCycle) {
            if (dist[a][c] != NEG_INF && dist[c][b] != NEG_INF) {
                cout << "infinitely kind\n";
                return 0;
            }
        }
    }

    // Otherwise reconstruct path
    vector<int> resultEdges;

    for (int t = 0; t + 1 < k; ++t) {
        int u = concerts[t];
        int v = concerts[t+1];

        if (dist[u][v] == NEG_INF) {
            // Should be impossible (problem says reachable)
            cout << "infinitely kind\n";
            return 0;
        }

        int cur = u;
        while (cur != v) {
            int nxt = nextv[cur][v];
            if (nxt == -1) {
                cout << "infinitely kind\n";
                return 0;
            }
            int eid = edgeId[cur][nxt];
            if (eid == -1) {
                cout << "infinitely kind\n";
                return 0;
            }
            resultEdges.push_back(eid);
            cur = nxt;
        }
    }

    cout << resultEdges.size() << "\n";
    for (int i = 0; i < (int)resultEdges.size(); ++i) {
        cout << resultEdges[i] << (i + 1 < resultEdges.size() ? ' ' : '\n');
    }

    return 0;
}
