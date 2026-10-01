#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> children;
vector<int> tin, tout;
int timer = 0;

void dfs(int v) {
    tin[v] = timer++;
    for (int u : children[v]) {
        dfs(u);
    }
    tout[v] = timer++;
}

bool is_ancestor(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    children.resize(n + 1);
    tin.resize(n + 1);
    tout.resize(n + 1);
    
    int root = 0;
    for (int i = 1; i <= n; i++) {
        int parent;
        cin >> parent;
        if (parent == 0) {
            root = i;
        } else {
            children[parent].push_back(i);
        }
    }
    
    // DFS для вычисления времени входа и выхода (стр. 23-24 лекции)
    dfs(root);
    
    int m;
    cin >> m;
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        cout << (is_ancestor(a, b) ? 1 : 0) << "\n";
    }
    
    return 0;
}
