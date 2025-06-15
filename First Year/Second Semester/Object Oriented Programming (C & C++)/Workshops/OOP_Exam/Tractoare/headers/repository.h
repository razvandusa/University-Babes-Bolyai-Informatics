#pragma once
#include <string>
#include <vector>
#include "domain.h"

class Repository {
public:
    Repository(std::string filename) : filename(move(filename)) {}

    void load_from_file();

    void write_to_file();

    int numarTractoareAcelasiTip(const std::string& tip);

    void add_tractor(const Tractor& tractor);

    bool exista_id(int id);

    std::vector<Tractor>& get_all() { return lista_tractoare; }

private:
    std::string filename;
    std::vector<Tractor> lista_tractoare;
};
