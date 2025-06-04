#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
using namespace std;

vector<tuple<int, int, int>> Prim(int V, vector<vector<pair<int, int>>> &adj) {
    vector<bool> inMST(V + 1, false);     // marcheaza nodurile existente deja in arborele MST
    inMST[1] = true;                      // presupunem ca începem din nodul 1
    vector<tuple<int, int, int>> MST;     // lista muchiilor incluse in MST: (u, v, cost)

    // Cat timp nu avem V - 1 muchii (adica arborele nu e complet)
    while (MST.size() < V - 1) {
        int minCost = INT_MAX;           // initializam costul minim cu un cost foarte mare
        int chosenU = -1, chosenV = -1;  // nodurile ce formeaza muchia aleasa

        // parcurgem toate nodurile deja incluse in MST
        for (int u = 1; u <= V; u++) {
            // daca nodul nu e inclus in MST sarim peste el
            if (!inMST[u])
                continue;

            // exploram toate muchiile de forma (u, v) care pleaca din nodul u
            for (auto x : adj[u]) {
                int v = x.first;
                int w = x.second;
                // daca v este deja in arborele MST atunci sarim peste el
                if (inMST[v])
                    continue;

                // actualizam muchia minima daca gasim un cost mai mic
                if (w < minCost) {
                    minCost = w;
                    chosenU = u;
                    chosenV = v;
                }
            }
        }

        // daca am gasit o muchie valida, o adaugam in MST
        if (chosenU != -1 && chosenV != -1) {
            inMST[chosenV] = true;  // carcam nodul v ca fiind inclus
            MST.push_back({chosenU, chosenV, minCost});  // salvam muchia
        }
    }

    return MST;  // returnam lista de muchii aleasa pentru MST
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<pair<int, int>>> adj(V + 1);

    int u, v, w;
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    auto MST = Prim(V, adj);

    for (auto x : MST) {
        cout << get<0>(x) << " " << get<1>(x) << " " << get<2>(x) << endl;
    }
}