#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>

IteratorColectie::IteratorColectie(const Colectie& referinta): col(referinta) {
	curent = 0;
}

void IteratorColectie::prim() {
	curent = 0;
}


void IteratorColectie::urmator() {
	curent += 1;
}


bool IteratorColectie::valid() const {
	if (curent < col.dim())
          return true;
    return false;
}



TElem IteratorColectie::element() const {
	if (!valid()) {
          throw std::exception();
	}
    return col.elemente[curent];
}
