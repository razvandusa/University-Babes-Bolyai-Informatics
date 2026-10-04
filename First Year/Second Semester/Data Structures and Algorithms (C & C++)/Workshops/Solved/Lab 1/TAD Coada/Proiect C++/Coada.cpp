#include "Coada.h"
#include <exception>
#include <iostream>

using namespace std;


Coada::Coada() {
	dimensiune = 0;
    capacitate = 2;
    elemente = new TElem[capacitate];
}


void Coada::adauga(TElem elem) {
	if (dimensiune == capacitate) {
    	int newCapacitate = capacitate * 2;
        TElem* newElemente = new TElem[newCapacitate];
        for (int i = 0; i < dimensiune; i++) {
        	newElemente[i] = elemente[i];
        }
        delete[] elemente;
        capacitate = newCapacitate;
        elemente = newElemente;
	}
    elemente[dimensiune] = elem;
    dimensiune++;
}

//arunca exceptie daca coada e vida
TElem Coada::element() const {
	if (vida()) {
          throw std::exception();
    }
    return elemente[0];
}

TElem Coada::sterge() {
	if (vida()) {
		throw std::exception();
	}
    TElem removed = elemente[0];
	for (int i = 0; i < dimensiune - 1; i++) {
          elemente[i] = elemente[i + 1];
	}
    dimensiune--;
    return removed;
}

bool Coada::vida() const {
	return dimensiune == 0;
}


Coada::~Coada() {
	delete[] elemente;
}

