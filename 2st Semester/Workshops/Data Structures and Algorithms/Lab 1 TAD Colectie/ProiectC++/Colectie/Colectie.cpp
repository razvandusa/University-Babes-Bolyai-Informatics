#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


Colectie::Colectie() {
	dimensiune = 0;
    capacitate = 2;
    elemente = new TElem[capacitate];
}


void Colectie::adauga(TElem elem) {
	if (dimensiune == capacitate) {
		int newCapacitate = capacitate * 2;
		TElem* newElemente = new TElem[newCapacitate];
		for (int i = 0; i < dimensiune; i++) {
		    newElemente[i] = elemente[i];
		}
		elemente = newElemente;
		capacitate = newCapacitate;
	}
    elemente[dimensiune] = elem;
    dimensiune++;
}


bool Colectie::sterge(TElem elem) {
	for (int i = 0; i < dimensiune; i++) {
		if (elemente[i] == elem) {
        	for (int j = i; j < dimensiune - 1; j++) {
            	elemente[j] = elemente[j + 1];
        	}
            dimensiune--;
            return true;
		}
	}
	return false;
}


bool Colectie::cauta(TElem elem) const {
	for (int i = 0; i < dimensiune; i++) {
		if (elemente[i] == elem) {
			return true;
		}
	}
	return false;
}

int Colectie::nrAparitii(TElem elem) const {
	int count = 0;
	for (int i = 0; i < dimensiune; i++) {
		if (elemente[i] == elem) {
        	count++;
		}
	}
    return count;
}


int Colectie::dim() const {
	return dimensiune;
}


bool Colectie::vida() const {
	return dimensiune == 0;
}


IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	delete[] elemente;
}