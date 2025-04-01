#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	this->poz = 0;
	this->curent = 0;
}

void IteratorMDO::prim(){
	this->poz = 0;
	this->curent = 0;
}

void IteratorMDO::urmator(){
	if (!valid()) throw std::exception();

	curent++;
	if (curent >= dict.perechi.element(poz).valori.dim()) {
	    poz++;
	    curent = 0;
	}
}

bool IteratorMDO::valid() const{
	return poz < dict.perechi.dim() && curent < dict.perechi.element(poz).valori.dim();
}

TElem IteratorMDO::element() const{
	return std::make_pair(dict.perechi.element(poz).cheie, dict.perechi.element(poz).valori.element(curent));
}
