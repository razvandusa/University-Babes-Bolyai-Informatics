#include "tests_service.h"
#include "../headers/repository.h"
#include "../headers/service.h"
#include <fstream>
#include <sstream>
#include <cassert>

#include <string>

static std::string filename = "/Users/razvandusa/CLionProjects/Produse/tests/tests_repository.txt";

static void clear_file() {
    Repository repository(filename);
    Service service(repository);
    service.write_to_file();
}

static void test_add_produs() {
    Repository repository(filename);
    Service service(repository);
    try {
        service.add_produs("1", "Frigider", "Electrocasnic", "30");
        assert(true);
    } catch (...) {
        assert(false);
    }
    try {
        service.add_produs("abc", "Frigider", "Electrocasnic", "30");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        service.add_produs("1", "Frigider", "Electrocasnic", "abc");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        service.add_produs("1", "Frigider", "Electrocasnic", "30");
        assert(false);
    } catch (...) {
        assert(true);
    }
    assert(service.get_all().size() == 1);
}

static void test_write_to_file() {
    clear_file();
    Repository repository(filename);
    Service service(repository);
    service.add_produs("1", "Frigider", "Electrocasnic", "30");
    service.add_produs("2", "Masina_de_spalat", "Electrocasnic", "24");
    service.write_to_file();

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
        assert(pret == 30);
    }

    {
        std::getline(fin, line);
        std::istringstream iss(line);
        iss >> id >> nume >> tip >> pret;
        assert(id == 2);
        assert(nume == "Masina_de_spalat");
        assert(tip == "Electrocasnic");
        assert(pret == 24);
    }
}

static void test_load_from_file() {
    clear_file();
    Repository repository(filename);
    Service service(repository);
    service.add_produs("1", "Frigider", "Electrocasnic", "30");
    service.add_produs("2", "Masina_de_spalat", "Electrocasnic", "24");
    service.write_to_file();
    service.load_from_file();
    assert(service.get_all().size() == 2);
}

void tests_service() {
    test_add_produs();
    test_write_to_file();
    test_load_from_file();
}