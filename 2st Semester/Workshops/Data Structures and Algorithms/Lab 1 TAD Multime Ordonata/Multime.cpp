#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
//BC = WC = Θ(1)
//TC = Θ(1)
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

Multime::Multime() {
	/* de adaugat */
}

//BC = Θ(1)
//WC = O(n)
//TC = O(n)
bool Multime::adauga(TElem elem) {
	if (cauta(elem))
		return false;

	int poz = 0;
	//O(n)
	while (poz < elemente.dim() && rel(elemente.element(poz), elem)) {
		poz++;
	}

	elemente.adaugare(elem);

	//O(n)
	for (int i = elemente.dim() - 1; i > poz; --i) {
		elemente.element(i) = elemente.element(i - 1);
	}
	elemente.element(poz) = elem;

	return true;
}


//BC = Θ(n)
//WC = Θ(n)
//TC = Θ(n)
bool Multime::sterge(TElem elem) {
	//O(n)
	for (int i = 0; i < elemente.dim(); ++i) {
		if (elemente.element(i) == elem) {
			elemente.sterge(i);
			return true;
		}
	}
	return false;
}

//BC = Θ(1)
//WC = Θ(n)
//TC = O(n)
bool Multime::cauta(TElem elem) const {
	//O(n)
	for (int i = 0; i < elemente.dim(); i++) {
		if (elemente.element(i) == elem) {
			return true;
		}
	}
	return false;
}

//BC = WC = Θ(1)
//TC = Θ(1)
int Multime::dim() const {
	return elemente.dim();
	return 0;
}


//BC = WC = Θ(1)
//TC = Θ(1)
bool Multime::vida() const {
	return elemente.dim() == 0;
}

//BC = WC = Θ(1)
//TC = Θ(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}


Multime::~Multime() {
}

//BC : Θ(m * n)
//WC : Θ(m * n)
//O(m * n)
void Multime::reuniune(const Multime& b) {
	IteratorMultime it(b);
	it.prim();
	while (it.valid()) {
		adauga(it.element());
		it.urmator();
	}
}




