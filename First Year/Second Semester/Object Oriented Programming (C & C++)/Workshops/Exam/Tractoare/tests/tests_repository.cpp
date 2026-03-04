#include "tests_repository.h"
#include <cassert>
#include <iostream>
#include <__ostream/basic_ostream.h>

#include "../headers/repository.h"

static std::string filename = "/Users/razvandusa/CLionProjects/Tractoare/tests/tests_input.txt";

static void clear_file() {
    Repository repo(filename);
    repo.get_all().clear();
    repo.write_to_file();
}

static void write_to_file() {
    Repository repo(filename);
    clear_file();
    std::vector<Tractor>& lista_tractoare = repo.get_all();
    lista_tractoare.emplace_back(1, "test", "test", 6);
    lista_tractoare.emplace_back(2, "test", "test", 4);
    repo.write_to_file();
}

static void test_load_from_file() {
    Repository repo(filename);
    repo.load_from_file();
    assert(repo.get_all().size() == 2);
}

static void test_numar_tractoare_acelasi_tip() {
    Repository repo(filename);
    repo.load_from_file();
    assert(repo.numarTractoareAcelasiTip("test") == 2);
}

void tests_repository() {
    write_to_file();
    test_load_from_file();
    test_numar_tractoare_acelasi_tip();
}