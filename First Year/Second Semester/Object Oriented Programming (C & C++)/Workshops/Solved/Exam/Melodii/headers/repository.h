#pragma once
#include <string>
#include <vector>

#include "domain.h"

class Repository {
public:
    Repository(std::string filename) : filename(std::move(filename)) {}

    void write_to_file();

    void load_from_file();

    int count_rank(int rank) const;

    void update_melodie(int id, const std::string& titlu, int rank);

    void delete_melodie(int id);

    int count_artist(const std::string& artist) const;

    std::vector<Melodie>& get_melodii() { return lista_melodii; }

private:
    std::string filename;
    std::vector<Melodie> lista_melodii;
};
