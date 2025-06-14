#include "tests_repository.h"
#include "../headers/repository.h"
#include "../headers/domain.h"
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QtCore/qtextstream.h>

std::string filename = "/Users/razvandusa/CLionProjects/Produse/tests/tests_repository.txt";

static void clear_file() {
    Repository repository(filename);
    repository.write_to_file();
}

static void test_exista_produs() {
    Repository repository(filename);
    assert(repository.exista_produs(1) == false);
    auto produs_1 = Produs(1, "Frigider", "Electrocasnic", 3000);
    repository.add_produs(produs_1);
    assert(repository.exista_produs(1) == true);
}

static void test_add_produs() {
    Repository repository(filename);
    auto produs_1 = Produs(1, "Frigider", "Electrocasnic", 3000);
    auto produs_2 = Produs(2, "Masina_de_spalat", "Electrocasnic", 2400);
    repository.add_produs(produs_1);
    repository.add_produs(produs_2);
    assert(repository.get_all().size() == 2);
}

static void test_write_to_file() {
    clear_file();
    Repository repository(filename);
    auto produs_1 = Produs(1, "Frigider", "Electrocasnic", 3000);
    auto produs_2 = Produs(2, "Masina_de_spalat", "Electrocasnic", 2400);
    repository.add_produs(produs_1);
    repository.add_produs(produs_2);
    repository.write_to_file();

    std::ifstream fin(filename);
    std::string line;
    int id;
    std::string nume;
    std::string tip;
    double pret;

    {
        std::getline(fin, line);
        std::istringstream iss(line);
        iss >> id >> nume >> tip >> pret;
        assert(id == 1);
        assert(nume == "Frigider");
        assert(tip == "Electrocasnic");
        assert(pret == 3000);
    }

    {
        std::getline(fin, line);
        std::istringstream iss(line);
        iss >> id >> nume >> tip >> pret;
        assert(id == 2);
        assert(nume == "Masina_de_spalat");
        assert(tip == "Electrocasnic");
        assert(pret == 2400);
    }
}

static void test_load_from_file() {
    clear_file();
    Repository repository(filename);
    auto produs_1 = Produs(1, "Frigider", "Electrocasnic", 3000);
    auto produs_2 = Produs(2, "Masina_de_spalat", "Electrocasnic", 2400);
    repository.add_produs(produs_1);
    repository.add_produs(produs_2);
    repository.write_to_file();
    repository.load_from_file();
    assert(repository.get_all().size() == 2);
}

void tests_repository() {
    test_add_produs();
    test_exista_produs();
    test_load_from_file();
    test_write_to_file();
}