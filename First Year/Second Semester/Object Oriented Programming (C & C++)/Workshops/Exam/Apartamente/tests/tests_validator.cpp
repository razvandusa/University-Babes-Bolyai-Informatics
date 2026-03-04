#include "tests_validator.h"
#include <cassert>
#include <string>

#include "../headers/domain.h"
#include "../headers/validator.h"

void test_validator_id() {
    std::vector<Apartament> lista_apartamente;
    Apartament ap(0, "30m^2", "Barc_II", 30000);
    lista_apartamente.push_back(ap);

    std::string id = "123";
    assert(Validator::id_valid(id,lista_apartamente) == true);
    id = "0";
    assert(Validator::id_valid(id,lista_apartamente) == false);
    id = "";
    assert(Validator::id_valid(id,lista_apartamente) == false);
    id = "abc";
    assert(Validator::id_valid(id,lista_apartamente) == false);
    id = " 12 32";
    assert(Validator::id_valid(id,lista_apartamente) == false);
}

void test_validator_suprafata() {
    std::string suprafata = "40m^2";
    assert(Validator::suprafata_valida(suprafata) == true);
    suprafata = "";
    assert(Validator::suprafata_valida(suprafata) == false);
    suprafata = "abc";
    assert(Validator::suprafata_valida(suprafata) == false);
    suprafata = "12 32";
    assert(Validator::suprafata_valida(suprafata) == false);
    suprafata = "40";
    assert(Validator::suprafata_valida(suprafata) == false);
    suprafata = "123M^2";
    assert(Validator::suprafata_valida(suprafata) == false);
    suprafata = "abcm^2";
    assert(Validator::suprafata_valida(suprafata) == false);
}

void test_validator_strada() {
    std::string strada = "Barc_I";
    assert(Validator::strada_valida(strada) == true);
    strada = "Barc I";
    assert(Validator::strada_valida(strada) == false);
    strada = "";
    assert(Validator::strada_valida(strada) == false);
}

void test_validator_pret() {
    std::string pret = "20000";
    assert(Validator::pret_valid(pret) == true);
    pret = "";
    assert(Validator::pret_valid(pret) == false);
    pret = " 20000";
    assert(Validator::pret_valid(pret) == false);
}

void tests_validator() {
    test_validator_id();
    test_validator_suprafata();
    test_validator_strada();
    test_validator_pret();
}