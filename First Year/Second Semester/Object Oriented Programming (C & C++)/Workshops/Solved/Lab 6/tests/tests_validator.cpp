#include "../headers/validator.h"
#include <cassert>

void test_id_valid() {
    Validator validator;
    int id = -20;
    assert(validator.id_valid(id) == false);
    id = 100;
    assert(validator.id_valid(id) == true);
}

void test_denumire_valida() {
    Validator validator;
    std::string denumire = "Matematica";
    assert(validator.denumire_valida(denumire) == true);
    denumire = "Random";
    assert(validator.denumire_valida(denumire) == false);
}

void test_ore_valide() {
    Validator validator;
    int ore = 1000;
    assert(validator.ore_valide(ore) == false);
    ore = 50;
    assert(validator.ore_valide(ore) == true);
}

void test_tip_valid() {
    Validator validator;
    std::string tip = "Obligatorie";
    assert(validator.tip_valid(tip) == true);
    tip = "Random";
    assert(validator.tip_valid(tip) == false);
}
void teste_validator() {
    test_id_valid();
    test_denumire_valida();
    test_ore_valide();
    test_tip_valid();
}