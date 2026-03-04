#include "tests_repository.h"

#include <iostream>
#include <string>
#include <cassert>

#include "../headers/repository.h"

std::string filename = "/Users/razvandusa/CLionProjects/Biblioteca/tests/tests_file.txt";
void load_file() {
    std::ofstream fout(filename);
    fout << "1 2540 Cartea Ioan_Slavici roman\n"
            "2 2640 Baltagul Ioan_Slavici poezie\n"
            "3 2340 Povesti_din_copilarie Ioan_Slavici roman\n"
            "4 2940 Noroc Ioan_Slavici roman\n"
            "5 2140 Albinuta Ioan_Slavici poezie\n"
            "6 2140 Randunica Ioan_Slavici roman\n"
            "7 2140 Sarpele Ioan_Slavici eseu\n"
            "8 2140 Maimuta Ioan_Slavici roman\n"
            "9 2140 Paianjen Ioan_Slavici thriller\n"
            "10 2140 Musca Ioan_Slavici roman";
}

void test_load_from_file() {
    load_file();
    Repository repository(filename);
    repository.load_from_file();
    assert(repository.get_all().size() == 10);
}

void test_write_to_file() {
    load_file();
    Repository repository(filename);
    repository.load_from_file();
    repository.write_to_file();
    repository.load_from_file();
    assert(repository.get_all().size() == 10);
}

void tests_repository() {
    test_load_from_file();
    test_write_to_file();
}