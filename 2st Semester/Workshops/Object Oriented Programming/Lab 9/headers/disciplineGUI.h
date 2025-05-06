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

    /*
     *  Functia load_data incarca in lista_discipline lista din service
     */
    void load_data();

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
