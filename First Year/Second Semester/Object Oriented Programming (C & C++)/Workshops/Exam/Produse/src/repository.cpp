#include "../headers/repository.h"
#include <fstream>

void Repository::load_from_file() {
    lista_produse.clear();
    std::ifstream fin(filename);
    int id;
    std::string nume;
    std::string tip;
    double pret;
    while (fin >> id >> nume >> tip >> pret) {
        lista_produse.emplace_back(id, nume, tip, pret);
    }
}

void Repository::write_to_file() const {
    std::ofstream fout(filename);
    for (auto produs : lista_produse) {
        fout << produs.get_id() << " " << produs.get_nume() << " " << produs.get_tip() << " " << produs.get_pret() << std::endl;
    }
}

bool Repository::exista_produs(const int id) const {
    for (auto produs : lista_produse) {
        if (produs.get_id() == id) {
            return true;
        }
    }
    return false;
}

bool Repository::exista_tip(std::string tip) const {
    for (auto produs : lista_produse) {
        if (produs.get_tip() == tip) {
            return true;
        }
    }
    return false;
}
