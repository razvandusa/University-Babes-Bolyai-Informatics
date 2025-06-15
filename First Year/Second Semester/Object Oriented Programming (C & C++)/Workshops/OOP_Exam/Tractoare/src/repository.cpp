#include "../headers/repository.h"
#include "fstream"

void Repository::load_from_file() {
    int id, numarRoti;
    std::string denumire, tip;
    std::ifstream fin(filename);
    while (fin >> id >> denumire >> tip >> numarRoti) {
        lista_tractoare.emplace_back(id, denumire, tip, numarRoti);
    }
}

void Repository::write_to_file() {
    std::ofstream fout(filename);
    for (auto& tractor : lista_tractoare) {
        fout << tractor.get_id() << " " << tractor.get_denumire() << " " << tractor.get_tip() << " " << tractor.get_numarRoti() << std::endl;
    }
}

int Repository::numarTractoareAcelasiTip(const std::string& tip) {
    int count = 0;

    for (auto& tractor : lista_tractoare) {
        if (tractor.get_tip() == tip) {
            count++;
        }
    }

    return count;
}

void Repository::add_tractor(const Tractor &tractor) {
    lista_tractoare.push_back(tractor);
}

bool Repository::exista_id(const int id) {
    for (const auto& tractor : lista_tractoare) {
        if (tractor.get_id() == id) {
            return true;
        }
    }
    return false;
}

