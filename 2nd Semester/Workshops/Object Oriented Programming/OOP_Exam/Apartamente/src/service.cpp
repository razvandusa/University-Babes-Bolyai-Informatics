#include "../headers/service.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "../headers/validator.h"

void Service::load_from_file_service() {
    const std::string& filename = repository.get_filename();
    std::ifstream fin(filename);

    std::string line;
    while (getline(fin,line)) {
        std::istringstream iss(line);
        std::string id;
        std::string suprafata;
        std::string strada;
        std::string pret;
        iss >> id >> suprafata >> strada >> pret;
        if (!Validator::id_valid(id, repository.get_all())) {
            throw std::invalid_argument("Id-ul nu este valid : " + id);
        }
        if (!Validator::suprafata_valida(suprafata)) {
            throw std::invalid_argument("Suprafata nu este valida : " + suprafata);
        }
        if (!Validator::strada_valida(strada)) {
            throw std::invalid_argument("Strada nu este valida : " + strada);
        }
        if (!Validator::pret_valid(pret)) {
            throw std::invalid_argument("Pretul nu este valid : " + pret);
        }
    }
    repository.load_from_file();
}

void Service::write_to_file_service() {
    repository.write_to_file();
}

void Service::delete_apartament_service(int id) {
    repository.delete_apartament(id);
}

std::vector<Apartament> Service::filtreaza_suprafata(const std::string& min, const std::string& max) const {
    int int_min, int_max;
    try {
        int_min = std::stoi(min);
    } catch (...) {
        throw std::invalid_argument("Invalid min : " + min);
    }

    try {
        int_max = std::stoi(max);
    } catch (...) {
        throw std::invalid_argument("Invalid max : " + max);
    }

    std::vector<Apartament> lista_filtrata;
    std::ranges::copy_if(get_all(),std::back_inserter(lista_filtrata),
                         [int_min,int_max](const Apartament& ap) {
                             int suprafata = stoi(ap.get_suprafata().substr(0,ap.get_suprafata().size()-3));
                             return int_min <= suprafata && int_max >= suprafata;
                         });
    return lista_filtrata;
}

std::vector<Apartament> Service::filtreaza_pret(const std::string& min, const std::string& max) const {
    int int_min, int_max;
    try {
        int_min = std::stoi(min);
    } catch (...) {
        throw std::invalid_argument("Invalid min : " + min);
    }

    try {
        int_max = std::stoi(max);
    } catch (...) {
        throw std::invalid_argument("Invalid max : " + max);
    }

    std::vector<Apartament> lista_filtrata;
    std::ranges::copy_if(get_all(),std::back_inserter(lista_filtrata),[int_min,int_max](const Apartament& ap) {
        int pret = ap.get_pret();
        return int_min <= pret && int_max >= pret;
    });

    return lista_filtrata;
}

std::vector<Apartament> &Service::get_all() const {
    return repository.get_all();
}
