#include "IteratorMultime.h"
#include "Multime.h"

//BC = WC = Θ(1)
//TC = Θ(1)
IteratorMultime::IteratorMultime(const Multime& m): mult(m) {
	curent = 0;
}

//BC = WC = Θ(1)
//TC = Θ(1)
TElem IteratorMultime::element() const {
	if (!valid())
		return -1;
	return mult.elemente.element(curent);
}

//BC = WC = Θ(1)
//TC = Θ(1)
bool IteratorMultime::valid() const {
	return curent < mult.elemente.dim();
}

//BC = WC = Θ(1)
//TC = Θ(1)
void IteratorMultime::urmator() {
	curent++;
}

//BC = WC = Θ(1)
//TC = Θ(1)
void IteratorMultime::prim() {
	curent = 0;
}

