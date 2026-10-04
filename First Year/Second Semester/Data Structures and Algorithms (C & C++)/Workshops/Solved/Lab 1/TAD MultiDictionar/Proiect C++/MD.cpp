#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;


MD::MD() {
	dimensiune = 0;
    capacitate = 2;
    elemente = new Nod[capacitate];
}


void MD::adauga(TCheie c, TValoare v) {
	if (dimensiune == capacitate) {
        int newCapacitate = capacitate * 2;
    	Nod* newElemente = new Nod[newCapacitate];
        for (int i = 0; i < dimensiune; i++) {
        	newElemente[i] = elemente[i];
        }
        delete [] elemente;
        capacitate = newCapacitate;
        elemente = newElemente;
    }

	for (int i = 0; i < dimensiune; i++) {
		if (elemente[i].cheie == c) {
			elemente[i].valori.push_back(v);
			return;
		}
	}

	elemente[dimensiune].cheie = c;
	elemente[dimensiune].valori = {v};
	dimensiune++;
}


bool MD::sterge(TCheie c, TValoare v) {
	for (int i = 0; i < dimensiune; i++) {
    	if (elemente[i].cheie == c) {
        	for (int j = 0; j < elemente[i].valori.size(); j++) {
            	if (elemente[i].valori[j] == v) {
                	elemente[i].valori.erase(elemente[i].valori.begin() + j);
            		if (elemente[i].valori.empty()) {
            			for (int k = i; k < dimensiune - 1; k++) {
                        	elemente[k] = elemente[k + 1];
            			}
                        dimensiune--;
            		}
                    return true;
            	}
        	}
    	}
	}
	return false;
}


vector<TValoare> MD::cauta(TCheie c) const {
	for (int i = 0; i < dimensiune; i++) {
    	if (elemente[i].cheie == c) {
        	return elemente[i].valori;
    	}
	}
	return vector<TValoare>();
}


int MD::dim() const {
	int total = 0;
	for (int i = 0; i < dimensiune; i++) {
    	total += elemente[i].valori.size();
	}
    return total;
}


bool MD::vid() const {
	return dim() == 0;
}

IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}


MD::~MD() {
	delete [] elemente;
}
