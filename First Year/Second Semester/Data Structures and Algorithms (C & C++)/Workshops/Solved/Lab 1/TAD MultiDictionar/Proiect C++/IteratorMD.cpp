#include "IteratorMD.h"

#include <iostream>
#include <ostream>

#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	curent_cheie = 0;
    curent_valoare = 0;
}

TElem IteratorMD::element() const{
  	TCheie cheie = md.elemente[curent_cheie].cheie;
    TValoare valoare = md.elemente[curent_cheie].valori[curent_valoare];
	return pair <TCheie, TValoare>  (cheie, valoare);
}

bool IteratorMD::valid() const {
	return curent_cheie < md.dimensiune;
}

void IteratorMD::urmator() {
	if (curent_valoare < md.elemente[curent_cheie].valori.size() - 1) {
    	curent_valoare++;
	}
    else {
        curent_valoare = 0;
    	curent_cheie++;
    }
}

void IteratorMD::prim() {
	curent_cheie = 0;
    curent_valoare = 0;
}

