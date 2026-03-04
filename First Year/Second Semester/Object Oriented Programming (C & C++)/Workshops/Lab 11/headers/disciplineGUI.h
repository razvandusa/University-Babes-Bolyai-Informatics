#pragma once
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>
#include <vector>
#include <string>

#include "contract.h"
#include "service.h"

class DisciplineGUI : public QWidget {
public:
    DisciplineGUI(Service& serv) : service(serv) {
        init_GUI();
        load_data();
        init_connections();
    }

    /*
     *  Functia load_data incarca in lista_discipline lista din service
     */
    void load_data();

private:
    Service& service;
    QListWidget* lista_GUI = new QListWidget();
    QTableWidget* tabel_GUI = new QTableWidget();

    QLineEdit* id_GUI = new QLineEdit();
    QLineEdit* denumire_GUI = new QLineEdit();
    QLineEdit* ore_GUI = new QLineEdit();
    QLineEdit* tip_GUI = new QLineEdit();
    QLineEdit* cadru_didactic_GUI = new QLineEdit();

    QPushButton* exit_button = new QPushButton("&Exit");
    QPushButton* adauga_button = new QPushButton("&Adauga");
    QPushButton* sterge_button = new QPushButton("&Sterge");
    QPushButton* modifica_button = new QPushButton("&Modifica");
    QPushButton* undo_button = new QPushButton("&Undo");
    QPushButton* sort_button = new QPushButton("&Sorteaza");
    QPushButton* filtreaza_button = new QPushButton("&Filtreaza");
    QPushButton* contract_button = new QPushButton("&Contract");

    /*
     *  Functia init_GUI creeaza si aranjeaza elementele vizuale lae interfetei grafice
     */
    void init_GUI();

    /*
     *  Functia init_connections va initializa conexiunile cu butoanele
     */
    void init_connections();

    /*
     *  Functia da clear la casutele de edit
     */
    void clear_line_edits();
};

class SortWindow : public QWidget {
public:
    SortWindow(Service& serv, DisciplineGUI* ptr) : service(serv), main_window_ptr(ptr) {
        init_GUI();
        init_connections();
    }

private:
    Service& service;
    DisciplineGUI* main_window_ptr;
    QPushButton* denumire_button = new QPushButton("&Denumire");
    QPushButton* numar_ore_button = new QPushButton("&Numar Ore");
    QPushButton* cadru_didactic_button = new QPushButton("&Cadru Didactic");
    QPushButton* tip_button = new QPushButton("&Tip");

    /*
     *  Functia init_GUI creeaza si aranjeaza elementele vizuale lae interfetei grafice
     */
    void init_GUI();

    /*
     *  Functia init_connections va initializa conexiunile cu butoanele
     */
    void init_connections();
};

class FiltreazaWindow : public QWidget {
public:
    FiltreazaWindow(Service& serv) : service(serv) {
        init_GUI();
        init_connections();
    }
private:

    Service& service;
    QListWidget* lista_filtrata_GUI = new QListWidget();

    QLineEdit* ore_GUI = new QLineEdit();
    QLineEdit* cadru_didactic_GUI = new QLineEdit();

    QPushButton* numar_ore_button = new QPushButton("&Numar Ore");
    QPushButton* cadru_didactic_button = new QPushButton("&Cadru Didactic");

    /*
     *  Functia load_data incarca in lista_discipline lista din service
     */
    void load_data(std::vector<Disciplina>& lista_discipline) const;

    /*
     *  Functia init_GUI creeaza si aranjeaza elementele vizuale lae interfetei grafice
     */
    void init_GUI();

    /*
     *  Functia init_connections va initializa conexiunile cu butoanele
     */
    void init_connections();

    /*
     *  Functia da clear la casutele de edit
     */
    void clear_line_edits();
};

class ContractGUI : public QWidget {
public:
    ContractGUI(Service& serv) : service(serv) {
        init_GUI();
        init_connections();
    }

    /*
     *  Functia load_data incarca in contract lista
     */
    void load_data(const std::vector<Disciplina>& lista_discipline) const;

private:
    Service& service;
    Contract contract;
    QListWidget* lista_contract_GUI = new QListWidget();

    QLineEdit* id_GUI = new QLineEdit();
    QLineEdit* numar_contracte_generat_GUI = new QLineEdit();
    QLineEdit* export_contracte_GUI = new QLineEdit();

    QPushButton* adauga_button = new QPushButton("&Adauga");
    QPushButton* goleste_contract = new QPushButton("&Goleste Contract");
    QPushButton* generare_button = new QPushButton("&Genereaza");
    QPushButton* exporta_button = new QPushButton("&Exporta");
    QPushButton* exit_button = new QPushButton("&Exit");

    /*
     *  Functia init_GUI creeaza si aranjeaza elementele vizuale lae interfetei grafice
     */
    void init_GUI();

    /*
     *  Functia init_connections va initializa conexiunile cu butoanele
     */
    void init_connections();

    /*
     *  Functia da clear la casutele de edit
     */
    void clear_line_edits();
};