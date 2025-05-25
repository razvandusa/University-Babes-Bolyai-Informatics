#include "tests_domain.h"
#include <cassert>
#include "../headers/domain.h"

void test_constructor() {
    Carte c(1,2540,"Cartea","Ioan_Slavici","roman");
    assert(c.get_id() == 1);
    assert(c.get_cod() == 2540);
    assert(c.get_titlu() == "Cartea");
    assert(c.get_autor() == "Ioan_Slavici");
    assert(c.get_gen() == "roman");
}
void tests_domain() {
    test_constructor();
}