#include "Matrice.h"

#include <exception>

using namespace std;

bool rel(int lin1, int col1, int lin2, int col2) {
	if (lin1 < lin2) {
		return true;
	}
	else if (lin1 == lin2 && col1 < col2) {
		return true;
	}
	else {
		return false;
	}
}

Matrice::Matrice(int m, int n) {
    if (m < 0 || n < 0) {
    	throw exception();
    }
    nrLin = m;
    nrCol = n;
    relatie = rel;
    head = nullptr;
}



int Matrice::nrLinii() const{
	return nrLin;
	return 0;
}


int Matrice::nrColoane() const{
	return nrCol;
	return 0;
}


TElem Matrice::element(int i, int j) const{
	if (i < 0 || j < 0 || i >= nrLin || j >= nrCol) {
    	throw exception();
	}

    Nod* temp = head;
    while (temp != nullptr && rel(temp->lin, temp->col, i, j)) {
    	temp = temp->next;
    }

    if (temp != nullptr && temp->lin == i && temp->col == j) {
    	return temp->val;
    }
    else {
    	return 0;
    }
}

TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || j < 0 || i >= nrLin || j >= nrCol) {
    	throw exception();
	}

    Nod* temp = head;
    Nod* anterior = nullptr;
    while (temp != nullptr && rel(temp->lin, temp->col, i, j)) {
      	anterior = temp;
    	temp = temp->next;
    }

    if (head == nullptr) { //Lista este goala
      	Nod* nodNou = new Nod;
        nodNou->lin = i;
        nodNou->col = j;
        nodNou->val = e;
        nodNou->next = nullptr;
        head = nodNou;

      	return 0;
   	}

    if (anterior == nullptr && head != nullptr) { //Nodul este capul listei
    	Nod* nodNou = new Nod;
    	nodNou->lin = i;
    	nodNou->col = j;
    	nodNou->val = e;
    	nodNou->next = head;
        head = nodNou;

        return 0;
    }

    if (temp!= nullptr && temp->lin == i && temp->col == j) { //Valoarea exista in lista
    	TElem valoareVeche = temp->val;
        temp->val = e;
        return valoareVeche;
    }

    if (temp != nullptr) { //Valoarea nu se afla in lista si nu este la finalul listei
    	Nod* nodNou = new Nod;
    	nodNou->lin = i;
    	nodNou->col = j;
    	nodNou->val = e;
    	nodNou->next = temp;

        anterior->next = nodNou;
        return 0;
    }

    if (temp == nullptr) { //Valoarea nu se afla in lista si este la finalul listei
    	Nod* nodNou = new Nod;
    	nodNou->lin = i;
    	nodNou->col = j;
    	nodNou->val = e;
    	nodNou->next = nullptr;
    	anterior->next = nodNou;

        return 0;
    }
}

Matrice::~Matrice() {
  	Nod* temp = head;
   	Nod* anterior = nullptr;
	while (temp != nullptr) {
    	anterior = temp;
        temp = temp->next;
        delete anterior;
	}
}