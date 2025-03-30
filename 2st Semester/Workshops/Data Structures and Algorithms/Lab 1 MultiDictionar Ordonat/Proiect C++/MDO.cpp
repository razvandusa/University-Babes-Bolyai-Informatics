#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

/*
Constructorul va retine relatia de ordine
r - relatia de ordine
 */
MDO::MDO(Relatie r) {
    this->relatie = r;
}

/*
Adauga va adauga in dictionar o cheie cu o valoare corespunzatoare
c - cheia
v - valoarea corespunzatoare cheii
 */
void MDO::adauga(TCheie c, TValoare v) {
  	//Cautam prin fiecare element din elementele dictionarului
    for (auto& nod : elemente) {
      	//Daca deja exista cheia in dictionar ii asignam inca o valoare si iesim din functie
    	if (nod.cheie == c){
          	nod.valori.push_back(v);
            return;
        }
    }
	//Daca nu exista cheia in dictionar trebuie sa cream un nou element, folosind structura de tip Nod care
    //retine o cheie si un vector de valori
    Nod nou;
    nou.cheie = c;
    nou.valori.push_back(v);
    //Cream un iterator care porneste de la inceputul vectorului de elemente
    auto it = elemente.begin();
    //Parcurgem vectorul pana gasim locul unde trebuie sa vina cheia in raport cu relatia de ordine
    while (it != elemente.end() && relatie(it->cheie, c)) {
        ++it;
    }
	//Inseram elementul in pozitia corecta pastrand ordinea definita de relatie
    elemente.insert(it, nou);
}

/*
Cauta in vectorul de elemente dupa cheie si returneaza valorile corespunzatoare cheii
c - cheia pe care o cautam
 */
vector<TValoare> MDO::cauta(TCheie c) const {
	//Cauta in vectorul de elemente elementul (nodul) care are cheia c si returneaza valorile corespunzatoare cheii
	for (const auto& nod : elemente) {
        if (nod.cheie == c) {
          	return nod.valori;
        }
	}
    //Daca nu am gasit elementul in vectorul de elemente atunci returnam un vector gol
    return {};
}

/*
Sterge din vectorul de noduri valoarea corespunzatoare cheii unui nod
c - cheia corespunzatoare nodului
v - valoarea din nod pe care o stergem
 */
bool MDO::sterge(TCheie c, TValoare v) {
	//Cautam cheia c in vectorul de noduri
	for (auto it = elemente.begin(); it != elemente.end(); ++it) {
        //Daca gasim cheia atunci cautam valoarea in lista de valori
        if (it->cheie == c) {
          	auto& valori = it->valori;
            for (auto vit = valori.begin(); vit != valori.end(); ++vit) {
              	 //Daca gasim valoarea atunci o stergem din lista de valori a nodului respectiv
             	 if (*vit == v) {
                    valori.erase(vit);
                    if (valori.empty()) {
                        // Daca vectorul de valori a devenit gol dupa stergere,
                        // inseamna ca cheia nu mai are nicio valoare asociata.
                        // Stergem si nodul din vectorul principal.
                        elemente.erase(it);
                    }
                    return true;
             	 }
            }
            return false;
        }
	}
    return false;
}

/*
Returneaza numarul de perechi cheie-valoare din vectorul de noduri
 */
int MDO::dim() const {
	int total = 0;
    //Pentru fiecare nod ii luam numarul de elemente => numarul de perechi
    for (const auto& nod : elemente) {
    	total += nod.valori.size();
    }
    return total;
}

/*
Verificam daca lista de noduri este vida
 */
bool MDO::vid() const {
	return elemente.empty();
}

/*
Creeaza si returneaza un iterator pentru dictionarul curent
 */
IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	/* de adaugat */
}
