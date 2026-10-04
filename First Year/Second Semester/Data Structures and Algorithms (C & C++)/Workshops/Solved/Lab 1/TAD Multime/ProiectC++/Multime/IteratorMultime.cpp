#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>


IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	curent = 0;
}


void IteratorMultime::prim() {
	curent = 0;
}


void IteratorMultime::urmator() {
	curent += 1;
}


TElem IteratorMultime::element() const {
	if (!valid()) {
    	throw std::exception();
	}
    return multime.elemente[curent];
}

bool IteratorMultime::valid() const {
	return curent < multime.dim();
}
