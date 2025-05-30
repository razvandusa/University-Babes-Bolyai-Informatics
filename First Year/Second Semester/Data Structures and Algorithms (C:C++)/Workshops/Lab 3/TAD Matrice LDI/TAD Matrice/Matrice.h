#pragma once

typedef int TElem;

typedef bool(*Relatie)(int lin1, int col1, int lin2, int col2);

bool rel(int, int, int, int);

#define NULL_TELEMENT 0

class Matrice {

private:
	/* aici e reprezentarea */
	int nrLin;
	int nrCol;
	Relatie relatie;
	struct Nod {
		int lin = 0;
		int col = 0;
		TElem val = 0;
		Nod* next = nullptr;
		Nod* prev = nullptr;
	};
	Nod* head;

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice();

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in TAD Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in TAD Matrice
	TElem modifica(int i, int j, TElem);

};