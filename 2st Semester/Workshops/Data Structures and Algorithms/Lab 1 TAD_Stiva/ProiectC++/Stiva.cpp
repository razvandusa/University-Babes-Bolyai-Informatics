#include "Stiva.h"
#include <exception>
#include <iostream>

using namespace std;


Stiva::Stiva() {
	dimensiune = 0;
    capacitate = 2;
    elemente = new TElem[capacitate];
}


void Stiva::adauga(TElem elem) {
	if (dimensiune == capacitate) {
        int newCapacitate = capacitate * 2;
    	TElem* newElemente = new TElem[newCapacitate];
        for (int i = 0; i < dimensiune; i++) {
        	newElemente[i] = elemente[i];
        }
        elemente = newElemente;
    }
    elemente[dimensiune++] = elem;
}

//arunca exceptie daca coada e vida
TElem Stiva::element() const {
	if (vida()) {
		throw std::exception();
	}
	return elemente[dimensiune - 1];
}

TElem Stiva::sterge() {
	if (vida()) {
          throw std::exception();
    }
    dimensiune--;
	return elemente[dimensiune];
}

bool Stiva::vida() const {
	return dimensiune == 0;
}


Stiva::~Stiva() {
	delete[] elemente;
}

