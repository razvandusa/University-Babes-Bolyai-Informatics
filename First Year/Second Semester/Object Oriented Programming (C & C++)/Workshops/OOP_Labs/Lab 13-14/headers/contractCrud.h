#pragma once
#include "observer.h"
#include "domain.h"
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <random>
#include <service.h>

class ContractCrud {
private:
    std::vector<Disciplina> cos;

public:

    /**
     * Constructor implicit care initializeaza un contract gol.
     */
    ContractCrud();

    /**
     * Sterge toate disciplinele din contract.
     */
    void clear_contract();

    /**
     * Adauga o disciplina in contract pe baza ID-ului dat.
     * @param id ID-ul disciplinei de adaugat.
     * @param service Serviciul care contine toate disciplinele disponibile.
     */
    void add_disciplina(int id, Service &service);

    /**
     * Genereaza un contract cu un numar aleator de discipline.
     * @param number_to_generate Numarul de discipline de adaugat.
     * @param service Serviciul care furnizeaza disciplinele.
     */
    void generate_contract(int number_to_generate, Service &service);

    /**
     * Incarca in contract o lista de discipline data.
     * @param lista_discipline Lista de discipline ce va inlocui contractul curent.
     */
    void reload_contract(std::vector<Disciplina>& lista_discipline);

    /**
     * Returneaza toate disciplinele din contract.
     * @return Vector de obiecte Disciplina din contract.
     */
    std::vector<Disciplina> getAll() const {
        return cos;
    }
};
