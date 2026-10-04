#include "VectorDinamic.h"
#include "IteratorVectorDinamic.h"
#include <exception>

using namespace std;

void VectorDinamic::redim() {
    int newCapacitate = capacitate * 2;
    TElem *newVector = new TElem[newCapacitate];
    for (int i = 0; i < capacitate; i++) {
        newVector[i] = vector[i];
    }
    delete [] vector;
    vector = newVector;
    capacitate = newCapacitate;
}


VectorDinamic::VectorDinamic(int cp) {
  	if (cp <= 0) {
          throw std::exception();
  	}
	capacitate = cp;
    dimensiune = 0;
    vector = new TElem[capacitate];
}



VectorDinamic::~VectorDinamic() {
	delete [] vector;
}



int VectorDinamic::dim() const{
	return dimensiune;
}



TElem VectorDinamic::element(int i) const{
	if (i < 0 || i >= dimensiune) {
          throw std::exception();
	}
	return vector[i];
}



void VectorDinamic::adaugaSfarsit(TElem e) {
  	if (dimensiune == capacitate) {
          redim();
  	}
	vector[dimensiune++] = e;
}


void VectorDinamic::adauga(int i, TElem e) {
  	if (i < 0 || i > dimensiune) {
          throw std::exception();
  	}
    for (int j = dimensiune; j > i; j--) {
    	vector[j] = vector[j - 1];
    }
    vector[i] = e;
    dimensiune++;
}


TElem VectorDinamic::modifica(int i, TElem e) {
	if (i < 0 || i >= dimensiune) {
          throw std::exception();
	}
    TElem old = vector[i];
    vector[i] = e;
    return old;
}


TElem VectorDinamic::sterge(int i) {
	if (i < 0 || i >= dimensiune) {
          throw std::exception();
	}
    TElem old = vector[i];
    for (int j = i; j < dimensiune - 1; j++) {
    	vector[j] = vector[j + 1];
    }
    dimensiune--;
    return old;
}

IteratorVectorDinamic VectorDinamic::iterator() {
	return IteratorVectorDinamic(*this);
}



