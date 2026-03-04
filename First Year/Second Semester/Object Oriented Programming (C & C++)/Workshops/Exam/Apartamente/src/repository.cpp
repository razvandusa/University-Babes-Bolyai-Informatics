#include "../headers/repository.h"
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>

void Repository::load_from_file() {
    std::ifstream fin(filename);

    std::string line;
    while (std::getline(fin,line)) {
        std::istringstream iss(line);
        int id;
        std::string suprafata;
        std::string strada;
        int pret;
        iss >> id >> suprafata >> strada >> pret;
        Apartament ap(id,suprafata,strada,pret);
        lista_apartamente.push_back(ap);
    }
}

void Repository::write_to_file() {
    std::ofstream fout(filename);
    for (const auto& ap : lista_apartamente) {
        fout << ap.get_id() << " " << ap.get_suprafata() << " " << ap.get_strada() << " " << ap.get_pret() << '\n';
    }
}

void Repository::delete_apartament(const int id) {
    for (auto iterator = lista_apartamente.begin(); iterator < lista_apartamente.end(); ++iterator) {
        if (iterator->get_id() == id) {
            lista_apartamente.erase(iterator);
        }
    }
    write_to_file();
}

std::string& Repository::get_filename() {
    return filename;
}

std::vector<Apartament>& Repository::get_all() {
    return lista_apartamente;
}