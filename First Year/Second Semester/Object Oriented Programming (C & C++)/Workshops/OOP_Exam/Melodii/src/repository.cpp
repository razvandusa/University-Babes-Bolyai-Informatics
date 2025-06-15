#include "../headers/repository.h"
#include <fstream>
#include <algorithm>

void Repository::load_from_file() {
    std::ifstream fin(filename);
    lista_melodii.clear();
    int id, rank;
    std::string titlu, artist;
    while (fin >> id >> titlu >> artist >> rank) {
        lista_melodii.emplace_back(id, titlu, artist, rank);
    }
}

void Repository::write_to_file() {
    std::ofstream fout(filename);
    for (const auto& melodie : lista_melodii) {
        fout << melodie.get_id() << " " << melodie.get_titlu() << " " << melodie.get_artist() << " " << melodie.get_rank() << std::endl;
    }
}

int Repository::count_rank(int rank) const {
    int count = 0;
    for (const auto& melodie : lista_melodii) {
        if (melodie.get_rank() == rank) {
            count++;
        }
    }

    return count;
}

void Repository::update_melodie(int id, const std::string& titlu, int rank) {
    for (auto& melodie : lista_melodii) {
        if (melodie.get_id() == id) {
            melodie.set_titlu(titlu);
            melodie.set_rank(rank);
        }
    }
}

void Repository::delete_melodie(const int id) {
    for (auto it = lista_melodii.begin(); it != lista_melodii.end(); ++it) {
        if (it->get_id() == id) {
            lista_melodii.erase(it);
            break;
        }
    }
}

int Repository::count_artist(const std::string& artist) const {
    int count = 0;
    for (const auto& melodie : lista_melodii) {
        if (melodie.get_artist() == artist) {
            count++;
        }
    }

    return count;
}
