#include <cassert>
#include <iostream>
#include "ProiectC++/Stiva.h"

using namespace std;


int main() {
    Stiva stiva;
    stiva.adauga(3);
    stiva.adauga(4);
    stiva.adauga(9);
    cout << stiva.element() << endl;
    stiva.sterge();
    cout << stiva.element() << endl;
    while (!stiva.vida()) {
        stiva.sterge();
    }
    try {
        stiva.sterge();
        assert(false);
    }catch (...) {
        assert(true);
    }
    return 0;
}
