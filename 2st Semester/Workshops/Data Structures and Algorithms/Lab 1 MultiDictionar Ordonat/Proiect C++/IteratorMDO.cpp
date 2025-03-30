#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d), curent(0){
	//S-a initializat dictionarul cu referinta catre MDO si curent cu 0
    //Pentru fiecare nod din elemente se adauga o pereche in vectorul de perechi
    for (const auto& nod : dict.elemente) {
    	for (const auto& val : nod.valori) {
         	perechi.push_back(std::make_pair(nod.cheie, val));
        }
    }
}

void IteratorMDO::prim(){
	curent = 0;
}

void IteratorMDO::urmator(){
	/* de adaugat */
    ++curent;
}

bool IteratorMDO::valid() const{
	/* de adaugat */
	return curent < perechi.size();
}

TElem IteratorMDO::element() const{
	//Returnam perechea de la pozitia curenta
    if (!valid()) {
      	throw std::out_of_range("Element is not valid");
    }
    return perechi[curent];
}


