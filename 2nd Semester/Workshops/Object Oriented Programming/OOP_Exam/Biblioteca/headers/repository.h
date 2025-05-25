#pragma once
#include <fstream>
#include <sstream>
#include "domain.h"
#include <vector>

class Repository {
public:
    /*
     *  Creeaza un repository cu un fisier
     *  filename : std::string
     */
    Repository(const std::string &filename) : filename(filename) {}

    /*
     *  Incarca din fisier datele
     */
    void load_from_file();

    /*
     *  Scrie in fisier datele
     */
    void write_to_file();

    /*
     *  Returneaza lista de carti din fisier
     *  lista_carti : std::vector<Carte>
     */
    std::vector<Carte>& get_all() {
        return lista_carti;
    }

private:
    std::vector<Carte> lista_carti;
    std::string filename;
};
