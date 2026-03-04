#include "tests_service.h"
#include <cassert>
#include <iostream>

#include "../headers/repository.h"
#include "../headers/service.h"
#include "../tests/tests_utils.h"

void test_convert_marimi() {
    Rochie r1(1,"GUCCI WOOL DRESS","XS",9000,"True");
    assert(Service::convert_marime(r1) == 0);
    Rochie r2(1,"GUCCI WOOL DRESS","S",9000,"True");
    assert(Service::convert_marime(r2) == 1);
    Rochie r3(1,"GUCCI WOOL DRESS","M",9000,"True");
    assert(Service::convert_marime(r3) == 2);
    Rochie r4(1,"GUCCI WOOL DRESS","L",9000,"True");
    assert(Service::convert_marime(r4) == 3);
    Rochie r5(1,"GUCCI WOOL DRESS","XL",9000,"True");
    assert(Service::convert_marime(r5) == 4);
    Rochie r6(1,"GUCCI WOOL DRESS","XXL",9000,"True");
    assert(Service::convert_marime(r6) == 5);
}

void test_sortare_marimi() {
    loading_file(filename);
    Repository repository(filename);
    Service service(repository);
    service.load_from_file();
    service.sortare_marime();

    auto lista_rochii = service.get_all();

    for (int i = 0; i < lista_rochii.size() - 1; i++) {
        assert(service.compara_marimi(lista_rochii[i], lista_rochii[i]));
    }
}

void test_sortare_pret() {
    loading_file(filename);
    Repository repository(filename);
    Service service(repository);
    service.load_from_file();
    service.sortare_pret();

    auto lista_rochii = service.get_all();

    for (int i = 0; i < lista_rochii.size() - 1; i++) {
        assert(lista_rochii[i].get_pret() <= lista_rochii[i].get_pret());
    }
}

void tests_service() {
    test_convert_marimi();
    test_sortare_marimi();
    test_sortare_pret();
}