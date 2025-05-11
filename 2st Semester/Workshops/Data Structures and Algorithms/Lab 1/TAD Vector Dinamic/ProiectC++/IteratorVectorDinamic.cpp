#include "IteratorVectorDinamic.h"
#include "VectorDinamic.h"
#include <exception>


IteratorVectorDinamic::IteratorVectorDinamic(const VectorDinamic& referinta) :

	vector(referinta) {
	curent = 0;
}



void IteratorVectorDinamic::prim() {
	curent = 0;
}



bool IteratorVectorDinamic::valid() const{
	return curent < vector.dim();
}



TElem IteratorVectorDinamic::element() const{
	if (!valid()) {
          throw std::exception();
	}
    return vector.element(curent);
}



void IteratorVectorDinamic::urmator() {
	curent += 1;
}

