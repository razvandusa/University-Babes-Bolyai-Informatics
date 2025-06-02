#include <iostream>
#include <vector>
using namespace std;

vector<int> BellmanFord(int V, vector<tuple<int, int, int>>& edges, int src) {
    vector<int> dist(V + 1, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= V; i++) {
        for (auto [u, w, v] : edges) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                if (i == V) {
                    return {-1};
                }
                dist[v] = dist[u] + w;
            }
        }
    }

    return dist;
}

int main() {
    int V, E, src;
    cin >> V >> E >> src;
    vector<tuple<int, int, int>> edges;

    for (int i = 0; i < E; i++) {
        int u, w, v;
        cin >> u >> w >> v;
        edges.push_back({u,w,v});
    }

    auto dist = BellmanFord(V, edges, src);
    for (int i = 1; i <= V; i++) {
        if (dist[i] == INT_MAX) {
            cout << -1 << " ";
        } else {
            cout << dist[i] << " ";
        }
    }
}