#pragma once
#include <QtWidgets/qwidget.h>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>

#include "service.h"

class GUI : public QWidget {
    private:
        Service& service;

        QListWidget *lista_gui;
        QPushButton *button_sterge = new QPushButton("Sterge");
        QPushButton *button_filtreaza_suprafata = new QPushButton("Filtreaza Suprafata");
        QPushButton *button_filtreaza_pret = new QPushButton("Filtreaza Pret");
        QLineEdit *line_edit_min = new QLineEdit();
        QLineEdit *line_edit_max = new QLineEdit();

    public:
    /*
     *  Constructor default
     */
    GUI(Service& service): service(service) {
        init_GUI();
        load_data();
        init_connections();
    }

    /*
    *  Incarca lista_gui cu elementele din lista
    */
    void load_data();

    /*
     *  Creeaza si aranjeaza elementele vizuale
     */
    void init_GUI();

    /*
     *  Initializeaza conexiunile
     */
    void init_connections();
};
