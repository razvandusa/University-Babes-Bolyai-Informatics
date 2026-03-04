#include "tests_domain.h"
#include "../headers/domain.h"
#include <cassert>

void test_constructor() {
    const Apartament ap(0, "50m^2", "Barc_I", 30000);
    assert(ap.get_id() == 0);
    assert(ap.get_suprafata() == "50m^2");
    assert(ap.get_strada() == "Barc_I");
    assert(ap.get_pret() == 30000);
}

void test_constructor_copiere() {
    const Apartament ap(0, "50m^2", "Barc_I", 30000);
    const Apartament& ap_copy = ap;
    assert(ap_copy.get_id() == 0);
    assert(ap_copy.get_suprafata() == "50m^2");
    assert(ap_copy.get_strada() == "Barc_I");
    assert(ap_copy.get_pret() == 30000);
}

void test_operator() {
    const Apartament ap1(0, "50m^2", "Barc_I", 30000);
    const Apartament ap2(1, "50m^2", "Barc_I", 30000);
    assert(ap1 == ap2);
    const Apartament ap3(2, "49m^2", "Barc_I", 30000);
    assert(ap1 != ap3);
    const Apartament ap4(3, "50m^2", "Barc_II", 30000);
    assert(ap1 != ap4);
    const Apartament ap5(4, "50m^2", "Barc_I", 29999);
    assert(ap1 != ap5);
}

void tests_domain() {
    test_constructor();
    test_constructor_copiere();
    test_operator();
}