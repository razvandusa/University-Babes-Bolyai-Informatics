#include "IteratorLP.h"
#include "Lista.h"
#include <exception>

IteratorLP::IteratorLP(const Lista& l):lista(l) {
    curent = l.head;
}

void IteratorLP::prim(){
    curent = lista.head;
}

void IteratorLP::urmator(){
    if (!valid()) {
        throw std::exception();
    }
    curent = curent->next;
}

bool IteratorLP::valid() const{
    return curent != nullptr;
}

TElem IteratorLP::element() const{
    if (!valid()) {
        throw std::exception();
    }
    return curent->element;
}


