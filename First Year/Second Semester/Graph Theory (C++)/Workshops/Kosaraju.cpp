#include <vector>
#include <iostream>
#include <queue>
#include <limits>
#include <stack>
using namespace std;

void dfs1(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& S) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v, adj, visited, S);
        }
    }
    S.push(u); // punem pe stiva la finalizarea nodului
}

void dfs2(int u, vector<vector<int>>& adjT, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";
    for (int v : adjT[u]) {
        if (!visited[v]) {
            dfs2(v, adjT, visited);
        }
    }
}

void Kosaraju(int V, vector<vector<int>>& adj) {
    stack<int> S;
    vector<bool> visited(V + 1, false);

    // Pas 1: DFS normal
    for (int i = 1; i <= V; ++i) {
        if (!visited[i]) {
            dfs1(i, adj, visited, S);
        }
    }

    // Pas 2: Construim transpusa
    vector<vector<int>> adjT(V + 1);
    for (int u = 1; u <= V; ++u) {
        for (int v : adj[u]) {
            adjT[v].push_back(u);
        }
    }

    // Pas 3: DFS pe transpusa
    fill(visited.begin(), visited.end(), false);
    cout << "Componente tare conexe:\n";
    while (!S.empty()) {
        int u = S.top();
        S.pop();
        if (!visited[u]) {
            dfs2(u, adjT, visited);
            cout << "\n"; // fiecare DFS descoperă o componentă
        }
    }
}

int main() {
    int V = 5;
    vector<vector<int>> adj(V + 1);

    adj[1] = {2};
    adj[2] = {3};
    adj[3] = {1};
    adj[4] = {5};

    Kosaraju(V, adj);

    return 0;
}