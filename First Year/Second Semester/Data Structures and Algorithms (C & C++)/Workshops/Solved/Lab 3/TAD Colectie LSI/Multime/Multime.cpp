#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Multime::Multime() {
	head = nullptr;
}


bool Multime::adauga(TElem elem) {
	Nod* temp = head;
    Nod* anterior = nullptr;

    while (temp != nullptr) {
    	if (temp->valoare == elem) {
        	temp->frecventa++;
            return false;
    	}
    	anterior = temp;
        temp = temp->next;
    }

    Nod* newNode = new Nod;
    newNode->valoare = elem;
	newNode->frecventa = 1;
    newNode->next = nullptr;

    if (head == nullptr) { //Lista este goala, adaug nodul la inceput
    	head = newNode;
    } else { //Adauga nodul la finalul listei
     	anterior->next = newNode;
    }
	return true;

}


bool Multime::sterge(TElem elem) {
	Nod* temp = head;
    Nod* anterior = nullptr;

    if (head == nullptr) { //Lista este goala
    	return false;
    }

    if (head->valoare == elem) { //Daca nodul este capul listei atunci setez capul la nullptr
    	head = head->next;
        delete temp;
        return true;
    }

    while (temp != nullptr) {
    	if (temp->valoare == elem) {
        	anterior->next = temp->next;
            delete temp;
            return true;
    	}
      	anterior = temp;
    	temp = temp->next;
    }
	return false;
}


bool Multime::cauta(TElem elem) const {
	Nod* temp = head;
    while (temp != nullptr) {
    	if (temp->valoare == elem) {
        	return true;
    	}
        temp = temp->next;
    }
	return false;
}


int Multime::dim() const {
	int contor = 0;

    Nod* temp = head;
    while (temp != nullptr) {
    	contor++;
        temp = temp->next;
    }

	return contor;
}

bool Multime::vida() const {
	return head == nullptr;
}


Multime::~Multime() {
	Nod* temp = head;
    while (temp != nullptr) {
    	Nod* anterior = temp;
        temp = temp->next;
        delete anterior;
    }
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

