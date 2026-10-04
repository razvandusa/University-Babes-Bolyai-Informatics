#include "Iterator.h"
#include "DO.h"
#include <exception>

using namespace std;

Iterator::Iterator(const DO& d) : dict(d){
	curent = 0;
}

void Iterator::prim(){
	curent = 0;
}

void Iterator::urmator(){
	curent++;
}

bool Iterator::valid() const{
	return curent < dict.dim();
}

TElem Iterator::element() const{
	if (!valid()){
        	throw std::exception();
	}
    TCheie c = dict.elemente[curent].cheie;
	TValoare v = dict.elemente[curent].valoare;
	return pair <TCheie, TValoare>  (c, v);
}


