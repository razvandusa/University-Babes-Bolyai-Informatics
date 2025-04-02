#pragma once
#include "service.h"

class UI {
public:
    /*
     *  Afiseaza meniul
     */
    void menu();

    /*
     *  Ruleaza aplicatie
     */
    void run();

    /*
     *  Adauga o disciplina in lista
     */
    void add_disciplina_UI();

    /*
     *  Sterge o disciplina din lista
     */
    void remove_disciplina_UI();

    /*
     *  Modifica o disciplina din lista
     */
    void update_disciplina_UI();

    /*
     *  Afiseaza lista de discipline
     */
    void show_list_UI();

    /*
     *  Filtreaza lista de discipline
     */
    void filtrare_discipline_UI();

    /*
     *  Sorteaza lista de discipline
     */
    void sortare_discipline_UI();
private:
    Service service;
};
