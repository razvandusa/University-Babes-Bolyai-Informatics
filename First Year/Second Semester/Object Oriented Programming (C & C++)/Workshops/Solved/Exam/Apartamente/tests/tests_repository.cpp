#include "tests_repository.h"
#include <cassert>
#include <fstream>
#include <iostream>

#include "../headers/repository.h"

const std::string filename = "/Users/razvandusa/CLionProjects/Apartamente/tests/tests_file.txt";
void loading_file() {
    std::ofstream fout(filename);
    fout << 0 << " " << "50m^2" << " " << "Barc_I" << " " << 30000;
}

void test_load_from_file() {
    loading_file();
    Repository repository(filename);
    repository.load_from_file();
    assert(repository.get_all().size() == 1);
}

void test_write_to_file() {
    loading_file();
    Repository repository(filename);
    repository.load_from_file();
    assert(repository.get_all().size() == 1);
    repository.write_to_file();
    assert(repository.get_all().size() == 1);
}

void test_delete_apartament() {
    loading_file();
    Repository repository(filename);
    repository.load_from_file();
    assert(repository.get_all().size() == 1);
    repository.delete_apartament(0);
    assert(repository.get_all().empty());
}

void test_get_filename() {
    Repository repository(filename);
    assert(repository.get_filename() == filename);
}

void tests_repository() {
    test_load_from_file();
    test_write_to_file();
    test_delete_apartament();
    test_get_filename();
}
