#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) {
	this->relatie = r;
}

void MDO::adauga(TCheie c, TValoare v) {
	int i = 0;
	// Cautam prin perechi locul unde se afla cheia
	while (i < this->perechi.dim() && this->perechi.element(i).cheie != c) {
		i++;
	}

	if (i < this->perechi.dim()) {
		// Cheia exista deja deci o sa adaugam in vectorul de valori valoarea
		this->perechi.element(i).valori.adaugare(v);
	} else {
		// Nu exista cheia asa ca o sa cream o pereche noua pe care o adaugam in dictionar
		Pereche perecheNoua;
		perecheNoua.cheie = c;
		perecheNoua.valori.adaugare(v);

		// Cautam poziția corecta de inserare
		int j = 0;
		while (j < this->perechi.dim() && !relatie(c, this->perechi.element(j).cheie)) {
			j++;
		}

		this->perechi.inserare(j, perecheNoua);
	}
}

vector<TValoare> MDO::cauta(TCheie c) const {
	vector<TValoare> rezultat;
	// Cautam cheia prin perechi
	for (int i = 0; i < this->perechi.dim(); i++) {
		if (this->perechi.element(i).cheie == c) {
			// Daca o gasim, returnam vectorul de perechi
			IteratorVectorDinamic<TValoare> it = this->perechi.element(i).valori.iterator();
			for (it.prim(); it.valid(); it.urmator()) {
				rezultat.push_back(it.element());
			}
			break;
		}
	}
	return rezultat;
}

bool MDO::sterge(TCheie c, TValoare v) {
	// Cautam cheia prin perechi
	for (int i = 0; i < this->perechi.dim(); i++) {
		if (this->perechi.element(i).cheie == c) {
			VectorDinamic<TValoare>& valori = this->perechi.element(i).valori;
			int j = 0;
			// Stergem valorile egale cu v
			while (j < valori.dim()) {
				if (valori.element(j) == v) {
					valori.sterge(j);
					// Daca nu mai are valori cheia, atunci stergem perechea
					if (valori.dim() == 0) {
						this->perechi.sterge(i);
					}
					return true;
				}
				j++;
			}
		}
	}
	return false;
}

int MDO::dim() const {
	int total = 0;
	// Luam fiecare pereche si numaram cate valori exista pentru fiecare cheie
	for (int i = 0; i < this->perechi.dim(); i++) {
		total += this->perechi.element(i).valori.dim();
	}
	return total;
}

bool MDO::vid() const {
	return this->dim() == 0;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
}
