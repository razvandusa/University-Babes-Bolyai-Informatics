//Dijkstra - algoritm pentru găsirea drumului minim de la un nod sursă s la toate nodurile
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

vector<int> Dijkstra(int V, vector<vector<pair<int, int>>> &adj, int src) {
    // Coada cu prioritati : (distanta, nod)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Vector de distante, initializat cu infinit
    vector<int> dist(V + 1, INT_MAX);

    // Inseram nodul sursa cu distanta 0
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto &x : adj[u]) {
            int weight = x.first;
            int v = x.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int V, E, src;
    cin >> V >> E >> src;
    /*
     * Input example
     * 5 6 4
     * 1 3 1
     * 2 1 2
     * 4 2 1
     * 4 3 8
     * 5 3 5
     * 5 4 2
    */

    //pereche(cost, vecin)
    vector<vector<pair<int, int>>> adj(V + 1);

    int u, v, w;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
    }

    auto dist = dijkstra(V, adj, src);
    for (int i = 1; i <= V; i++) {
        if (dist[i] == INT_MAX) {
            cout << -1 << " ";
        } else {
            cout << dist[i] << " ";
        }
    }
}
