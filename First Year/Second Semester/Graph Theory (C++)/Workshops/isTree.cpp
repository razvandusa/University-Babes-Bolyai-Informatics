#include <iostream>
#include <vector>
#include <iostream>
using namespace std;

bool Cycle(int u, int parent, vector<vector<int>> &adj, vector<bool> &visited) {
    visited[u] = true;
    for (auto v : adj[u]) {
        if (!visited[v]) {
            if (Cycle(v, u, adj, visited)) return true;
        }
        else if (visited[v] && v != parent) {
            return true;
        }
    }
    return false;
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<int>> adj(V + 1);
    vector<bool> visited(V + 1, false);

    // Verificam daca are V - 1 muchii
    if (E != V - 1) {
        cout << "Not a tree, it must have V - 1 edges!" << endl;
        return 0;
    }

    // Reading all the edges
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Verificam daca gasim cicluri
    if (Cycle(1, -1, adj, visited)) {
        cout << "Not a tree, there is a cycle!" << endl;
        return 0;
    }

    // Verificam conexiunea
    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            cout << "Not a tree, the graph is not conex!" << endl;
            return 0;
        }
    }

    cout << "It is a tree!" << endl;
    return 0;
}