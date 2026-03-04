#pragma once
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <set>

#include "repository.h"
#include <vector>

#include "observer.h"

class Service : public Subject {
public:
    Service(const Repository& repository) : repository(repository) {};

    /**
     * Valideaza datele si adauga produsul in lista
     * @param id id-ul produsului pe care il adaugam
     * @param nume numele produsului pe care il adaugam
     * @param tip tipul produsului pe care il adaugam
     * @param pret pretul produsului pe care il adaugam
     */
    void add_produs(const std::string& id, std::string nume, std::string tip, const std::string& pret);

    /**
     * Verifica daca exista un produs cu un anumit tip in lista
     * @param tip tipul produsului pe care il cautam
     * @return true || false in functi daca exista sau nu produsul cu tipul precizat
     */
    bool exista_tip(std::string tip);

    /**
     * Functia scrie in fisier lista de produse
     */
    void write_to_file();

    /**
     * Functia incarca din fisier lista de produse
     */
    void load_from_file();

    /**
     * Functia returneaza lista de produse
     * @return lista de produse
     */
    std::vector<Produs> get_all() {
        return repository.get_all();
    }

private:
    Repository repository;
};
