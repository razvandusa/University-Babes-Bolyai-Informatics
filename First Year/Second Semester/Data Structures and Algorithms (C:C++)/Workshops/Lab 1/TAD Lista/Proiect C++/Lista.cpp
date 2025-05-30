#include <exception>
#include "IteratorLP.h"
#include "Lista.h"
#include <iostream>

Lista::Lista() {
	head = nullptr;
    tail = nullptr;
}

int Lista::dim() const {
    int count = 0;
    Nod* curent = head;
    while (curent != nullptr) {
        count++;
        Nod* next = curent->next;
        curent = next;
    }
    return count;
}


bool Lista::vida() const {
    return head == nullptr;
}

IteratorLP Lista::prim() const {
    return IteratorLP(*this);
}

TElem Lista::element(IteratorLP poz) const {
    if (!poz.valid()) {
        throw std::exception();
    }
    return poz.element();
}

TElem Lista::sterge(IteratorLP& poz) {
    if (!poz.valid()) {
        throw std::exception();
    }

    Nod* nodDeSters = poz.curent;
    TElem elementDeSters = nodDeSters->element;
    if (nodDeSters->prev != nullptr) {
        nodDeSters->prev->next = nodDeSters->next;
    }
    else {
        head = nodDeSters->next;
    }

    if (nodDeSters->next != nullptr) {
        nodDeSters->next->prev = nodDeSters->prev;
    }
    else {
        tail = nodDeSters->prev;
    }

    poz.curent = nodDeSters->next;
    delete nodDeSters;
    return elementDeSters;
}

IteratorLP Lista::cauta(TElem e) const{
    auto iterator = IteratorLP(*this);
    while (iterator.valid()) {
        if (iterator.curent->element == e) {
            return iterator;
        }
        iterator.urmator();
    }
    return iterator;
}

TElem Lista::modifica(IteratorLP poz, TElem e) {
    if (!poz.valid()) {
        throw std::exception();
    }
    TElem vechi = poz.element();
    poz.curent->element = e;
    return vechi;
}

void Lista::adauga(IteratorLP& poz, TElem e) {
    if (!poz.valid()) {
        throw std::exception();
    }
    Nod* nodNou = new Nod;
    nodNou->element = e;
    nodNou->prev = poz.curent;
    nodNou->next = poz.curent->next;
    if (nodNou->next == nullptr) {
        tail = nodNou;
    }
    else {
        nodNou->next->prev = nodNou;
    }
    poz.curent->next = nodNou;
    poz.curent = nodNou;
}

void Lista::adaugaInceput(TElem e) {
    Nod* nodNou = new Nod;
    nodNou->element = e;
    nodNou->prev = nullptr;
    nodNou->next = head;
    if (head == nullptr) {
        tail = nodNou;
        head = nodNou;
    }
    else {
        head->prev = nodNou;
    }
    head = nodNou;
}

void Lista::adaugaSfarsit(TElem e) {
    Nod* nodNou = new Nod;
    nodNou->element = e;
    nodNou->next = nullptr;
    nodNou->prev = tail;
    if (tail == nullptr) {
        tail = nodNou;
        head = nodNou;
    }
    else {
        tail->next = nodNou;
    }
    tail = nodNou;
}

Lista::~Lista() {
    Nod* curent = head;
    while (curent != nullptr) {
        Nod* next = curent->next;
        delete curent;
        curent = next;
    }
}
