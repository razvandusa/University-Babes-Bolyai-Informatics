#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>
#include <vector>
#include <string>
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
