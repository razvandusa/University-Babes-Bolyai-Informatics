#include <iostream>
#include <fstream>
using namespace std;
constexpr int max_n = 101;
int matrice_de_adiacenta[max_n][max_n] = {0};
int matrice_de_incidenta[max_n][max_n] = {0};
int muchie[max_n][max_n] = {0};
bool visited[max_n] = {false};
int noduri;
struct lista_de_adiacenta
{
    queue <int> q;
};
struct lista_de_muchii
{
    int nod_1 = 0;
    int nod_2 = 0;
};
int main()
{
    ifstream fin("/Users/razvandusa/Documents/C++/Algoritmica Grafurilor/lab1/in.txt");
    fin >> noduri;

    //Fisier -> Matrice de adiacenta
    int nod_1,nod_2;
    while (fin >> nod_1 >> nod_2)
    {
        matrice_de_adiacenta[nod_1][nod_2] = 1;
        matrice_de_adiacenta[nod_2][nod_1] = 1;
    }

    cout << "Matrice de adiacenta\n";
    for (int i = 1; i <= noduri ; i++,cout<<endl)
    {
        for (int j = 1; j <= noduri; j++)
        {
            cout << matrice_de_adiacenta[i][j] << ' ';
        }
    }

    //Matrice de adiacenta -> Lista de adiacenta
    lista_de_adiacenta lista_adiacenta[noduri + 1];
    cout << "\nLista de adiacenta\n";
    for (int i = 1; i <= noduri; i++,cout<<endl)
    {
        cout << i << " : ";
        for (int j = 1; j <= noduri ;j++)
        {
            if (matrice_de_adiacenta[i][j] == 1)
            {
                lista_adiacenta[i].q.push(j);
                cout << j << ' ';
            }
        }
    }

    //Lista adiacenta -> Matrice Incidenta
    lista_de_muchii lista_muchii[max_n];
    int ind = 0;
    for (int i = 1; i <= noduri; i++)
    {
        while (!lista_adiacenta[i].q.empty())
        {
            int j = lista_adiacenta[i].q.front();
            lista_adiacenta[i].q.pop();
            bool gasit = false;
            for (int k = 1; k <= ind ; k++)
            {
                if ((lista_muchii[k].nod_1 == i and lista_muchii[k].nod_2 == j) or (lista_muchii[k].nod_1 == j and lista_muchii[k].nod_2 == i))
                {
                    gasit = true;
                }
            }
            if (!gasit)
            {
                ind++;
                lista_muchii[ind].nod_1 = i;
                lista_muchii[ind].nod_2 = j;
            }
        }
    }

    for (int i = 1;i <= noduri; i++)
    {
        for (int j = 1; j <= ind; j++)
        {
            if (i == lista_muchii[j].nod_1 or i == lista_muchii[j].nod_2)
            {
                matrice_de_incidenta[i][j] = 1;
            }
        }
    }

    cout << "\nMatrice de incidenta\n";
    for (int i = 1; i <= noduri; i++, cout<<endl)
    {
        for (int j = 1; j <= noduri; j++)
        {
            cout<<matrice_de_incidenta[i][j]<<' ';
        }
    }

    //Matrice Incidenta -> Lista Adiacenta
    for (int i = 1; i <= noduri; i++)
    {
        for (int j = 1; j <= ind; j++)
        {
            if (i == lista_muchii[j].nod_1)
            {
                lista_adiacenta[i].q.push(lista_muchii[j].nod_2);
            }
            else if (i == lista_muchii[j].nod_2)
            {
                lista_adiacenta[i].q.push(lista_muchii[j].nod_1);
            }
        }
    }
    cout << "\nLista de adiacenta\n";
    for (int i = 1; i <= noduri ; i++,cout<<endl)
    {
        lista_de_adiacenta copie;
        copie.q = lista_adiacenta[i].q;
        cout << i << " : ";
        while (!copie.q.empty())
        {
            cout << copie.q.front() << ' ';
            copie.q.pop();
        }
    }

    //Lista Adiacenta -> Matrice Adiacenta
    int matrice_de_adiacenta[max_n][max_n] = {0};
    for (int i = 1; i <= noduri ;i++)
    {
        while (!lista_adiacenta[i].q.empty())
        {
            int j = lista_adiacenta[i].q.front();
            matrice_de_adiacenta[i][j] = 1;
            lista_adiacenta[i].q.pop();
        }
    }

    cout << "\nMatrice de adiacenta\n";
    for (int i = 1; i <= noduri; i++,cout<<endl)
    {
        for (int j = 1; j <= noduri; j++)
        {
            cout << matrice_de_adiacenta[i][j] << ' ';
        }
    }
}