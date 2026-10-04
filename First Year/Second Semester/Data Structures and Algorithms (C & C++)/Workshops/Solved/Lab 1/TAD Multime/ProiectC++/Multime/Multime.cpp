#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Multime::Multime() {
	dimensiune = 0;
    capacitate = 2;
    elemente = new TElem[capacitate];
}


bool Multime::adauga(TElem elem) {
	for (int i = 0; i < dimensiune; i++) {
    	if (elemente[i] == elem) {
    		return false;
    	}
	}
    if (dimensiune == capacitate) {
    	int newCapacitate = capacitate * 2;
        TElem* newElemente = new TElem[newCapacitate];
        for (int i = 0; i < dimensiune; i++) {
        	newElemente[i] = elemente[i];
        }
        delete[] elemente;
        elemente = newElemente;
        capacitate = newCapacitate;
    }
	elemente[dimensiune++] = elem;
    return true;
}


bool Multime::sterge(TElem elem) {
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


bool Multime::cauta(TElem elem) const {
	for(int i = 0; i < dimensiune; i++) {
    	if (elemente[i] == elem) {
        	return true;
    	}
	}
	return false;
}


int Multime::dim() const {
	return dimensiune;
}

bool Multime::vida() const {
	return dimensiune == 0;
}


Multime::~Multime() {
	delete[] elemente;
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

