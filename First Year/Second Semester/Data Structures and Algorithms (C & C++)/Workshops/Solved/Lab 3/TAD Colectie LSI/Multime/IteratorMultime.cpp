#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>

IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	currentNod = multime.head;
}


void IteratorMultime::prim() {
	currentNod = multime.head;
}


void IteratorMultime::urmator() {
  	if (!valid()) {
    	throw std::exception();
    }
	currentNod = currentNod->next;
}


TElem IteratorMultime::element() const {
	if (valid()) {
    	return currentNod->valoare;
    }
    else {
    	throw std::exception();
    }
}

bool IteratorMultime::valid() const {
	return currentNod != nullptr;
}
