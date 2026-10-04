#include "tests_repository.h"
#include <cassert>
#include "../headers/repository.h"
#include "../headers/service.h"
static std::string filename = "/Users/razvandusa/CLionProjects/Melodii/tests/tests_input.txt";

static void clear_file() {
    Repository repo(filename);
    repo.write_to_file();
}

static void test_delete_melodie() {
    Repository repo(filename);
    clear_file();
    Service service(repo);
    std::vector<Melodie>& lista_melodii = service.get_melodii();
    lista_melodii.emplace_back(5, "Rockstar", "PostMalone", 2);
    try {
        service.delete_melodie(5);
        assert(false);
    } catch (...) {
        assert(true);
    }
    service.get_melodii().emplace_back(4, "Baby", "PostMalone", 3);
    assert(repo.get_melodii().size() == 2);
    service.delete_melodie(5);
    assert(repo.get_melodii().size() == 1);
}

void tests_service() {
    test_delete_melodie();
}