#include "tests_service.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include "../headers/repository.h"
#include "../headers/service.h"
std::string filename_service = "/Users/razvandusa/CLionProjects/Biblioteca/tests/tests_file.txt";
void load_file_service() {
    std::ofstream fout(filename_service);
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

void test_service_sortare() {
    load_file_service();
    Repository repository(filename_service);
    Service service(repository);
    service.load_from_file();
    service.sortare_titlu();
    std::vector<Carte> lista_carti = service.get_all();
    for (int i = 0 ; i - 1 <= lista_carti.size(); i++) {
        assert(lista_carti[i].get_titlu() < lista_carti[i + 1].get_titlu());
    }
}

void test_service_filtrare() {
    load_file_service();
    Repository repository(filename_service);
    Service service(repository);
    service.load_from_file();
    std::vector<Carte> lista_filtrata = service.filtrare_gen("roman");
    assert(lista_filtrata.size() == 6);
}

void test_write_to_file_service() {
    load_file_service();
    Repository repository(filename_service);
    Service service(repository);
    service.load_from_file();
    service.write_to_file();
    service.load_from_file();
    assert(repository.get_all().size() == 10);
}

void tests_service() {
    test_service_sortare();
    test_service_filtrare();
    test_write_to_file_service();
}