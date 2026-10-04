#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

Dictionar::Dictionar() {
	dimensiune = 0;
    capacitate = 2;
    elemente = new Nod[capacitate];
}

Dictionar::~Dictionar() {
	delete[] elemente;
}

TValoare Dictionar::adauga(TCheie c, TValoare v){
	for (int i = 0; i < dimensiune; i++) {
		if (elemente[i].cheie == c){
			TValoare old = elemente[i].valoare;
            elemente[i].valoare = v;
            return old;
		}
	}
	if (capacitate == dimensiune) {
        int newCapacitate = capacitate * 2;
		Nod* newElemente = new Nod[newCapacitate];
        for (int i = 0; i < dimensiune; i++) {
        	newElemente[i] = elemente[i];
        }
        delete[] elemente;
        capacitate = newCapacitate;
        elemente = newElemente;
	}
    elemente[dimensiune].cheie = c;
    elemente[dimensiune].valoare = v;
    dimensiune += 1;
	return NULL_TVALOARE;
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const{
	for (int i = 0; i < dimensiune; i++) {
    	if (elemente[i].cheie == c){
        	return elemente[i].valoare;
    	}
	}
	return NULL_TVALOARE;
}


TValoare Dictionar::sterge(TCheie c){
	for (int i = 0; i < dimensiune; i++) {
    	if (elemente[i].cheie == c){
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


int Dictionar::dim() const {
	return dimensiune;
}

bool Dictionar::vid() const{
	return dimensiune == 0;
}


IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}


