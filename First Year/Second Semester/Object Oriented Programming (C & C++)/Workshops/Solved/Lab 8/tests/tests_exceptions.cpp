#include "../headers/exceptions.h"
#include "tests_exceptions.h"
#include <cassert>

void test_constructor_exceptions() {
    Exception exceptie("Eroare");
    assert(exceptie.get_message() == "Eroare");
}

void teste_exceptions() {
    test_constructor_exceptions();
}