#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

DO::DO(Relatie r) {
	dimensiune = 0;
    capacitate = 2;
    elemente = new Nod[capacitate];
	rel = r;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	if (dimensiune == capacitate) {
        int newCapacitate = capacitate * 2;
		Nod* newElemente = new Nod[newCapacitate];
        for (int i = 0; i < dimensiune; i++) {
        	newElemente[i] = elemente[i];
        }
        delete[] elemente;
        elemente = newElemente;
        capacitate = newCapacitate;
	}
    for (int i = 0; i < dimensiune; i++) {
    	if (elemente[i].cheie == c) {
        	TValoare old = elemente[i].valoare;
            elemente[i].valoare = v;
            return old;
       	}
    }
    int poz = 0;
    while (poz < dimensiune && rel(elemente[poz].cheie,c)) {
    	poz++;
    }
    for (int i = dimensiune; i > poz; i--) {
    	elemente[i] = elemente[i - 1];
    }
    elemente[poz].cheie = c;
    elemente[poz].valoare = v;
    dimensiune += 1;
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	for (int i = 0; i < dimensiune; i++) {
    	if (elemente[i].cheie == c) {
        	return elemente[i].valoare;
    	}
	}
	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	for (int i = 0; i < dimensiune; i++) {
		if (elemente[i].cheie == c) {
            TValoare old = elemente[i].valoare;
			for (int j = i; j < dimensiune - 1; j++) {
            	elemente[j] = elemente[j + 1];
			}
            dimensiune -= 1;
            return old;
		}
	}
	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	return dimensiune;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	return dimensiune == 0;
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {
	delete[] elemente;
}
