#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> bellman_ford(int src, int V, const vector<vector<pair<int, int>>> &adj) {
    // Cream vectorul de distante si il initializam cu infinit
    vector<int> dist(V + 1, INT_MAX);
    dist[src] = 0;
    // Parcurgem de V ori graful
    for (int i = 1; i <= V; i++) {
        // Luam fiecare nod din graf
        for (int u = 1; u <= V; u++) {
            // Luam fiecare nod adiacent cu u
            for (auto x : adj[u]) {
                int w = x.first;
                int v = x.second;
                // dist[u] trebuie sa fie != INT_MAX pentru ca altfel dist[u] + w ar fi mereu -2mld
                if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                    // Daca suntem la a V-a iteratie si am gasit un caz mai bun inseamna ca exista un ciclu negativ in graf
                    if (i == V) {
                        cout << "Ciclu detectat!";
                        exit(0);
                    }
                    dist[v] = dist[u] + w;
                }
            }
        }
    }
    
    return dist;
}

int main() {
    int V, E, src;
    cin >> V >> E >> src;
    vector<vector<pair<int, int>>> adj(V + 1);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> w >> v;
        adj[u].push_back({w, v});
    }

    auto dist = bellman_ford(src, V, adj);

    for (int i = 1; i <= V; i++) {
        if (dist[i] == INT_MAX) {
            cout << -1 << " ";
        } else {
            cout << dist[i] << " ";
        }
    }
}