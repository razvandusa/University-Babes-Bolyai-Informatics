#include "tests_repository.h"

#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

#include "../headers/repository.h"
#include "../tests/tests_utils.h"

void test_load_from_file() {
    loading_file(filename);
    Repository repository(filename);
    repository.load_from_file();
    assert(repository.get_all().size() == 10);
}

void test_write_to_file() {
    loading_file(filename);
    Repository repository(filename);
    repository.load_from_file();
    assert(repository.get_all().size() == 10);
    repository.write_to_file();
    repository.load_from_file();
    assert(repository.get_all().size() == 10);
}

void tests_repository() {
    test_load_from_file();
    test_write_to_file();
}