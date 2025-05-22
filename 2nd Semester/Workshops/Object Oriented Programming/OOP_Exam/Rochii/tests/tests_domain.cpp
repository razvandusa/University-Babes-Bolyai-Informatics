#include "tests_domain.h"
#include <cassert>
#include "../headers/domain.h"

void test_constructor() {
    Rochie r(1,"GUCCI WOOL DRESS","S",9000,"True");
    assert(r.get_cod() == 1);
    assert(r.get_denumire() == "GUCCI WOOL DRESS");
    assert(r.get_marime() == "S");
    assert(r.get_pret() == 9000);
    assert(r.get_disponibilitate() == "True");
}

void test_copy_constructor() {
    Rochie r1(1,"GUCCI WOOL DRESS","S",9000,"True");
    Rochie r(r1);
    assert(r.get_cod() == 1);
    assert(r.get_denumire() == "GUCCI WOOL DRESS");
    assert(r.get_marime() == "S");
    assert(r.get_pret() == 9000);
    assert(r.get_disponibilitate() == "True");
}

void test_equal() {
    Rochie r(1,"GUCCI WOOL DRESS","S",9000,"True");
    Rochie r1(2,"GUCCI WOOL DRESS","S",9000,"True");
    assert(r == r1);
    Rochie r2(2,"GUCCI WOOL SHIRT","S",9000,"True");
    assert(r != r2);
    Rochie r3(2,"GUCCI WOOL DRESS","M",9000,"True");
    assert(r != r3);
    Rochie r4(2,"GUCCI WOOL DRESS","S",1000,"True");
    assert(r != r4);
    Rochie r5(2,"GUCCI WOOL DRESS","S",9000,"False");
    assert(r != r5);
}

void tests_domain() {
    test_constructor();
    test_copy_constructor();
    test_equal();
}