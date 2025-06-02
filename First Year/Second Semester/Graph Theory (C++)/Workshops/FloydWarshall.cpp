#include <iostream>
using namespace std;

vector<vector<int>> matrix;

void FloydWarshall(int V, vector<vector<int>> &matrix) {
    for (int k = 1; k <= V; k++) {
        for (int i = 1; i <= V; i++) {
            for (int j = 1; j <= V; j++) {
                if (matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX) {
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                }
            }
        }
    }
}

int main() {
    int V, E;
    /* Input example :
    4 3
    3 10 4
    4 -60 2
    2 40 1
     */
    cin >> V >> E;
    vector<vector<int>> matrix(V + 1, vector<int>(V + 1, INT_MAX));
    for (int i = 1; i <= E; i++) {
        int u, w, v;
        cin >> u >> w >> v;
        matrix[i][i] = 0;
        matrix[u][v] = w;
    }

    FloydWarshall(V, matrix);
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            if (matrix[i][j] == INT_MAX) {
                cout << "Nu exista drum de la nodul " << i << " la nodul " << j << "\n";
            } else {
                cout << "Distanta de la nodul " << i << " la nodul " << j <<" este " << matrix[i][j] << "\n";
            }
        }
    }
}