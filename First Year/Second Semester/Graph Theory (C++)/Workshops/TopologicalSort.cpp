//Sortarea Topologica este o metoda de aranjare liniara a nodurilor unui graf orientat aciclic (DAG), astfel incat pentru fiecare muchie (u, v), nodul u apare inaintea lui v in ordine
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int n, vector<vector<int>> &adj, vector<bool> &visited, stack<int> &result) {
    visited[n] = true;
    for (int v : adj[n]) {
        if (!visited[v]) {
            dfs(v, adj, visited, result);
        }
    }
    result.push(n);
}

void TopologicalSort(int V, vector<vector<int>> &adj) {
    vector<bool> visited(V, false);
    stack<int> result;

    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            dfs(i, adj, visited, result);
        }
    }

    while (!result.empty()) {
        cout << result.top() << " ";
        result.pop();
    }
}

int main() {
    int V, E;
    /*
    Input example
    11 12
    1 2
    1 3
    1 4
    2 5
    2 6
    6 9
    6 10
    10 11
    7 11
    4 7
    3 7
    4 8
    */
    cin >> V >> E;
    vector<vector<int>> adj(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    topological_sort(V, adj);
}
