#include "tests_service.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include "../headers/repository.h"
#include "../headers/service.h"

const std::string filename = "/Users/razvandusa/CLionProjects/Apartamente/tests/tests_file.txt";

void test_load_from_service() {
    {
        std::ofstream fout(filename);
        fout << "0" << " " << "50m^2" << " " << "Barc_I" << " " << "30000";
        fout.close();
        Repository repository_valid(filename);
        Service service(repository_valid);
        try {
            service.load_from_file_service();
            assert(true);
        } catch (...) {
            assert(false);
        }
        assert(service.get_all().size() == 1);
    }

    {
        std::ofstream fout(filename);
        fout << "a" << " " << "50m^2" << " " << "Barc_I" << " " << "30000";
        fout.close();
        Repository repository_invalid(filename);
        Service service2(repository_invalid);
        try {
            service2.load_from_file_service();
            assert(false);
        } catch (...) {
            assert(true);
        }
    }

    {
        std::ofstream fout(filename);
        fout << "0" << " " << "50m^3" << " " << "Barc_I" << " " << "30000";
        fout.close();
        Repository repository_invalid(filename);
        Service service2(repository_invalid);
        try {
            service2.load_from_file_service();
            assert(false);
        } catch (...) {
            assert(true);
        }
    }

    {
        std::ofstream fout(filename);
        fout << "0" << " " << "50m^2" << " " << "" << " " << "";
        fout.close();
        Repository repository_invalid(filename);
        Service service2(repository_invalid);
        try {
            service2.load_from_file_service();
            assert(false);
        } catch (...) {
            assert(true);
        }
    }

    {
        std::ofstream fout(filename);
        fout << "0" << " " << "50m^2" << " " << "Barc_I" << " " << "abc";
        fout.close();
        Repository repository_invalid(filename);
        Service service2(repository_invalid);
        try {
            service2.load_from_file_service();
            assert(false);
        } catch (...) {
            assert(true);
        }
    }
}

void test_write_to_file_service() {
    Repository repository(filename);
    Service service(repository);
    try {
        service.write_to_file_service();
        assert(true);
    }catch (...) {
        assert(false);
    }
}

void test_filtreaza_suprafata() {
    Repository repository(filename);
    Service service(repository);
    std::ofstream fout(filename);
    fout << "0" << " " << "50m^2" << " " << "Barc_I" << " " << "30000\n";
    fout << "1" << " " << "120m^2" << " " << "Barc_II" << " " << "35000\n";
    fout << "2" << " " << "30m^2" << " " << "Barc_III" << " " << "32000";
    fout.close();
    service.load_from_file_service();
    try {
        auto lista_filtrata = service.filtreaza_suprafata("a", "40");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        auto lista_filtrata = service.filtreaza_suprafata("20", "b");
        assert(false);
    } catch (...) {
        assert(true);
    }
    auto lista_filtrata = service.filtreaza_suprafata("20","50");
    assert(lista_filtrata.size() == 2);
}

void test_filtreaza_pret() {
    Repository repository(filename);
    Service service(repository);
    std::ofstream fout(filename);
    fout << "0" << " " << "50m^2" << " " << "Barc_I" << " " << "30000\n";
    fout << "1" << " " << "120m^2" << " " << "Barc_II" << " " << "35000\n";
    fout << "2" << " " << "30m^2" << " " << "Barc_III" << " " << "32000";
    fout.close();
    service.load_from_file_service();
    try {
        auto lista_filtrata = service.filtreaza_pret("a", "40");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        auto lista_filtrata = service.filtreaza_pret("20", "b");
        assert(false);
    } catch (...) {
        assert(true);
    }
    auto lista_filtrata = service.filtreaza_pret("32000","36000");
    assert(lista_filtrata.size() == 2);
}

void tests_service() {
    test_load_from_service();
    test_write_to_file_service();
    test_filtreaza_suprafata();
    test_filtreaza_pret();
}