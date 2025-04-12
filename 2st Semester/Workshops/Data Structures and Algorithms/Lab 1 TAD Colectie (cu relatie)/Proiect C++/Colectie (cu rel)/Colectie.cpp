#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	return e1 <= e2;
}

Colectie::Colectie() {
  	dimensiune = 0;
  	capacitate = 2;
	elemente = new TElem[capacitate];
}

void Colectie::adauga(TElem e) {
	if (dimensiune == capacitate) {
        int newCapacitate = capacitate * 2;
		TElem* newElemente = new TElem[newCapacitate];
        for (int i = 0; i < dimensiune; i++) {
        	newElemente[i] = elemente[i];
        }
        capacitate = newCapacitate;
	}

    int poz = 0;
    while (poz < dimensiune && rel(elemente[poz], e)) {
     	poz++;
    }

    for (int i = dimensiune; i > poz; i--) {
        elemente[i] = elemente[i - 1];
    }
    elemente[poz] = e;
	dimensiune++;
}


bool Colectie::sterge(TElem e) {
	for (int i = 0; i < dimensiune; i++) {
		if (elemente[i] == e) {
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
