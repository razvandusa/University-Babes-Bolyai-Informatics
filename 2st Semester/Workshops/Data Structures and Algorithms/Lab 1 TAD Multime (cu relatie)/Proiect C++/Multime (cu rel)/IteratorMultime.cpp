#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>


IteratorMultime::IteratorMultime(const Multime& m): mult(m) {
	curent = 0;
}

TElem IteratorMultime::element() const {
  	if (!valid()) {
		throw std::exception();
    }
	return mult.elemente[curent];
}

bool IteratorMultime::valid() const {
	return curent < mult.dim();
}

void IteratorMultime::urmator() {
	curent += 1;
}

void IteratorMultime::prim() {
	curent = 0;
}

