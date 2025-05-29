#pragma once
#include "contract.h"
#include "service.h"

class UI {
public:
    /**
     * Constructor
     */
    UI(Service& serv) : service(serv) {}

    /**
     * Afiseaza meniul principal.
     */
    static void menu();

    /**
     * Afiseaza meniul pentru optiunile legate de contract.
     */
    static void menu_contract();

    /**
     * Ruleaza aplicatia.
     */
    void run();

    /**
     * Adauga o disciplina in lista.
     */
    void add_disciplina_UI();

    /**
     * Adauga o disciplina in contract.
     */
    void add_disciplina_contract_UI();

    /**
     * Sterge o disciplina din lista.
     */
    void remove_disciplina_UI();

    /**
     * Modifica o disciplina din lista.
     */
    void update_disciplina_UI();

    /**
     * Cauta o disciplina dupa ID in lista.
     */
    void find_disciplina_UI();

    /**
     * Afiseaza lista de discipline.
     */
    void show_list_UI();

    /**
     * Afiseaza lista de discipline din contract.
     */
    void show_list_contract_UI();

    /**
     * Filtreaza lista de discipline dupa criterii.
     */
    void filtrare_discipline_UI();

    /**
     * Sorteaza lista de discipline dupa criteriu ales.
     */
    void sortare_discipline_UI();

    /**
     * Genereaza discipline aleatoare in contract.
     */
    void generate_contract_UI();

    /**
     * Gestioneaza optiunile pentru contract.
     */
    void gestionare_contract_UI();

    /**
     * Exporta contractul in fisier.
     */
    void export_contract_UI();

    /**
     * Afiseaza raportul generat.
     */
    void raport_UI();

    /**
     * Realizeaza undo pentru ultima operatie.
     */
    void undo_UI();
private:
    Contract contract;
    Service& service;
    Validator validator;
};
