#ifndef TEST_ALL_H
#define TEST_ALL_H
//Functie pentru rularea testelor aferente tuturor modulelor
#include "teste_domain.h"
#include "teste_repo.h"
#include "teste_service.h"

//Apeleaza functiile de test aferente tuturor modulelor
void test_all() {
    test_all_domain();
    test_all_repo();
    test_all_service();
}

#endif
