#pragma once
#include "contract.h"
#include "service.h"

class UI {
public:
    /*
     *  Constructor
     */
    UI(Service& serv) : service(serv) {}

    /*
     *  Afiseaza meniul
     */
    static void menu();

    /*
     *  Afiseaza meniul pentru contract
     */
    static void menu_contract();

    /*
     *  Ruleaza aplicatie
     */
    void run();

    /*
     *  Adauga o disciplina in lista
     */
    void add_disciplina_UI();

    /*
     *  Adauga o disciplina in contract
     */
    void add_disciplina_contract_UI();

    /*
     *  Sterge o disciplina din lista
     */
    void remove_disciplina_UI();

    /*
     *  Modifica o disciplina din lista
     */
    void update_disciplina_UI();

    /*
     *  Cauta o disciplina din lista
     */
    void find_disciplina_UI();

    /*
     *  Afiseaza lista de discipline
     */
    void show_list_UI();

    /*
     *  Afiseaza lista de discipline din contract
     */
    void show_list_contract_UI();

    /*
     *  Filtreaza lista de discipline
     */
    void filtrare_discipline_UI();

    /*
     *  Sorteaza lista de discipline
     */
    void sortare_discipline_UI();

    /*
    *  Genereaza discipline random in contract
    */
    void generate_contract_UI();

    /*
     *  Gestionare contract
     */
    void gestionare_contract_UI();

    /*
     *  Exporta contractul
     */
    void export_contract_UI();

    /*
     *  Afiseaza raportul
     */
    void raport_UI();

    /*
     *  Realizeaza undo
     */
    void undo_UI();
private:
    Contract contract;
    Service& service;
    Validator validator;
};
