#pragma once
#include <string>
#include <utility>
#include <vector>
#include "domain.h"

class Repository {
public:
    Repository(std::string filename) : filename(std::move(filename)) {};

    /**
     * Scrie in fisier datele din lista
     */
    void write_to_file() const;

    /**
     * Incarca lista cu datele din fisier
     */
    void load_from_file();

    /**
     * Adauga un produs in lista
     * @param produs produsul pe care il adaugam in lista
     */
    void add_produs(const Produs& produs) {
        lista_produse.push_back(produs);
    }

    /**
     * Verifica daca exista un produs in lista
     * @param id id-ul produsului pe care il verificam
     * @return bool 1 sau 0 in functie daca exista sau nu produsul cu id-ul cautat
     */
    bool exista_produs(int id) const;

    /**
     * Verifica daca exista un anumit tip in lista
     * @param tip tipul pe care il verificam daca exista in lista
     * @return bool 1 sau 0 in functie daca exista sau nu produsul cu tipul cautat
     */
    bool exista_tip(std::string tip) const;

    /**
     * Returneaza lista de produse
     * @return std::vector<Produs> lista de produse
     */
    std::vector<Produs> get_all() {
        return lista_produse;
    }

private:
    std::string filename;
    std::vector<Produs> lista_produse;
};