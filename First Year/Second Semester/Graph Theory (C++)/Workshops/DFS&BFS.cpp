//BFS - algoritm simplu de căutare (Parcurgere în lățime)
//DFS - algoritm de parcurgere care explorează muchiile vârfurilor nou descoperite (Parcurgere în adâncime)
#include <iostream>
#include <fstream>
using namespace std;
int noduri;
constexpr int max_n = 101;
int matrice_adiacenta[max_n][max_n] = {0};
int matrice_distante[max_n][max_n] = {0};
int noduri_izolate[max_n] = {0};
int noduri_grad[max_n] = {0};
int distanta[max_n];
bool vizitat[max_n] = {false};
void resetare_distanta()
{
    for (int i = 1; i <= max_n-1; i++)
    {
        distanta[i] = -1;
    }
}

void DFS(int nod)
{
    vizitat[nod] = true;
    for (int i = 1; i <= noduri; i++)
    {
        if (matrice_adiacenta[nod][i] == 1 and !vizitat[i])
        {
            DFS(i);
        }
    }
}

void BFS(int nod, queue<int> q)
{
    q.push(nod);
    distanta[nod] = 0;
    while (!q.empty())
    {
        int nod_curent = q.front();
        q.pop();
        for (int i = 1; i <= noduri; i++)
        {
            if (matrice_adiacenta[nod_curent][i] == 1 and distanta[i] == -1)
            {
                q.push(i);
                distanta[i] = distanta[nod_curent] + 1;
            }
        }
    }
}

int main()
{
    ifstream fin("/Users/razvandusa/Documents/C++/Algoritmica Grafurilor/lab1/in.txt");
    fin >> noduri;

    int nod_1,nod_2;
    while (fin >> nod_1 >> nod_2)
    {
        noduri_izolate[nod_1] = noduri_izolate[nod_2] = 1;
        noduri_grad[nod_1] += 1;
        noduri_grad[nod_2] += 1;
        matrice_adiacenta[nod_1][nod_2] = 1;
        matrice_adiacenta[nod_2][nod_1] = 1;
    }

    //Noduri izolate
    cout << "Nodurile izolate din graf sunt : ";
    for (int i = 1; i <= noduri; i++)
    {
        if (noduri_izolate[i] == 0)
        {
            cout << i << ' ';
        }
    }

    //Regulat/Neregulat
    cout << "\nGraful este : ";
    bool regulat = true;
    for (int i = 1; i <= noduri-1; i++)
    {
        if (noduri_grad[i] != noduri_grad[i+1])
        {
            regulat = false;
            break;
        }
    }
    if (regulat)
    {
        cout << "regulat\n";
    }
    else cout << "neregulat\n";

    //Matricea distantelor
    for (int i = 1; i <= noduri; i++)
    {
        queue<int> q;
        resetare_distanta();
        BFS(i,q);
        for (int j = 1; j <= noduri; j++)
        {
            if (distanta[j] != -1 and i != j)
            {
                matrice_distante[i][j] = distanta[j];
            }
        }
    }

    cout << "Matricea distantelor : \n";
    for (int i = 1; i <= noduri; i++,cout<<endl)
    {
        for (int j = 1; j <= noduri; j++)
        {
            cout << matrice_distante[i][j] << ' ';
        }
    }

    //Conexitatea
    DFS(1);
    bool conex = true;
    for (int i = 1; i <= noduri; i++)
    {
        if (!vizitat[i])
        {
            conex = false;
            break;
        }
    }
    cout <<"Graful este : ";
    if (conex)
    {
        cout << "conex";
    }
    else cout << "neconex";
}
