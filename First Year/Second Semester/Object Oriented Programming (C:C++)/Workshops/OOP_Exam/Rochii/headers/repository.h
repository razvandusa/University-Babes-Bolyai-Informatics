#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include "domain.h"

class Repository {
private:
    std::string filename;
    std::vector<Rochie> lista_rochii;

public:
    Repository(std::string filename) : filename(std::move(filename)) {}

    void load_from_file();

    void write_to_file();

    std::vector<Rochie>& get_all() {
        return lista_rochii;
    }

    ~Repository() = default;
};
