#include "Matrice.h"

#include <exception>

using namespace std;


Matrice::Matrice(int m, int n) {
  	if (m <= 0 || n <= 0) {
          throw std::exception();
  	}
    this->m = m;
    this->n = n;
	elemente = new TElem*[m];
    for (int i = 0; i < m; i++) {
          elemente[i] = new TElem[n];
    }
}



int Matrice::nrLinii() const{
	return m;
}


int Matrice::nrColoane() const{
	return n;
}


TElem Matrice::element(int i, int j) const{
	if (i < 0 || j < 0 || i >= m || j >= n) {
          throw std::exception();
	}
	return elemente[i][j];
}



TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || j < 0 || i >= m || j >= n) {
          throw std::exception();
	}
    TElem old = elemente[i][j];
    elemente[i][j] = e;
    return old;
}


Matrice::~Matrice() {
	for (int i = 0; i < m; i++) {
		delete[] elemente[i];
	}
	delete[] elemente;
}