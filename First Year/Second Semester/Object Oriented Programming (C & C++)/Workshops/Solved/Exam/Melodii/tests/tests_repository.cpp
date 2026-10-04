#include "tests_repository.h"
#include <cassert>
#include "../headers/repository.h"
static std::string filename = "/Users/razvandusa/CLionProjects/Melodii/tests/tests_input.txt";

static void clear_file() {
    Repository repo(filename);
    repo.write_to_file();
}

static void test_load_from_file() {
    Repository repo(filename);
    clear_file();
    std::vector<Melodie>& lista_melodii = repo.get_melodii();
    lista_melodii.emplace_back(3, "DanceMonkey" , "TonesAndI", 3);
    repo.load_from_file();
    assert(lista_melodii.empty());
}

static void test_write_to_file() {
    Repository repo(filename);
    clear_file();
    std::vector<Melodie>& lista_melodii = repo.get_melodii();
    lista_melodii.emplace_back(5, "Rockstar" , "PostMalone", 2);
    lista_melodii.emplace_back(3, "DanceMonkey" , "TonesAndI", 3);
    repo.write_to_file();
    repo.load_from_file();
    assert(lista_melodii.size() == 2);
}

static void test_update_melodie() {
    Repository repo(filename);
    clear_file();
    std::vector<Melodie>& lista_melodii = repo.get_melodii();
    lista_melodii.emplace_back(5, "Rockstar" , "PostMalone", 2);
    lista_melodii.emplace_back(3, "DanceMonkey" , "TonesAndI", 3);
    repo.update_melodie(3, "BabyShark", 1);
    assert(lista_melodii[1].get_titlu() == "BabyShark");
}

static void test_delete_melodie() {
    Repository repo(filename);
    clear_file();
    std::vector<Melodie> &lista_melodii = repo.get_melodii();
    lista_melodii.emplace_back(5, "Rockstar", "PostMalone", 2);
    lista_melodii.emplace_back(3, "DanceMonkey", "TonesAndI", 3);
    repo.delete_melodie(3);
    assert(lista_melodii.size() == 1);
    assert(lista_melodii[0].get_titlu() == "Rockstar");
}

static void test_count_rank() {
    Repository repo(filename);
    clear_file();
    std::vector<Melodie> &lista_melodii = repo.get_melodii();
    lista_melodii.emplace_back(5, "Rockstar", "PostMalone", 2);
    lista_melodii.emplace_back(1, "Rockstar", "PostMalone", 2);
    lista_melodii.emplace_back(3, "DanceMonkey", "TonesAndI", 3);
    assert(repo.count_rank(2) == 2);
    assert(repo.count_rank(3) == 1);
}

static void test_count_artist() {
    Repository repo(filename);
    clear_file();
    std::vector<Melodie> &lista_melodii = repo.get_melodii();
    lista_melodii.emplace_back(5, "Rockstar", "PostMalone", 2);
    lista_melodii.emplace_back(1, "Rockstar", "PostMalone", 2);
    lista_melodii.emplace_back(3, "DanceMonkey", "TonesAndI", 3);
    assert(repo.count_artist("PostMalone") == 2);
    assert(repo.count_artist("TonesAndI") == 1);
}

void tests_repository() {
    test_load_from_file();
    test_write_to_file();
    test_update_melodie();
    test_delete_melodie();
    test_count_artist();
    test_count_rank();
}