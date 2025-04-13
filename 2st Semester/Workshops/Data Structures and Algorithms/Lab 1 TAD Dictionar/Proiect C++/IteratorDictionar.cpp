#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <exception>

using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d){
	curent = 0;
}


void IteratorDictionar::prim() {
	curent = 0;
}


void IteratorDictionar::urmator() {
	curent += 1;
}


TElem IteratorDictionar::element() const{
	if (!valid()){
    	throw std::exception();
    }

	return pair <TCheie, TValoare> (dict.elemente[curent].cheie, dict.elemente[curent].valoare);
}


bool IteratorDictionar::valid() const {
	return curent < dict.dim();
}

