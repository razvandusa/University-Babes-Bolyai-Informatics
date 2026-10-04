#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	curent = 0;
}

TElem IteratorColectie::element() const{
	if (!valid()){
    	throw std::exception();
    }
    return col.elemente[curent];
}

bool IteratorColectie::valid() const {
	return curent < col.dimensiune;
}

void IteratorColectie::urmator() {
	curent += 1;
}

void IteratorColectie::prim() {
	curent = 0;
}
