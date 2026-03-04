#pragma once
#include <QPushButton>

#include "service.h"
#include "QMessageBox"
#include "QListWidget"

class GUI : QWidget {
    private:
        Service& service;
        QListWidget* lista_gui;
        QPushButton* button_inchiriere = new QPushButton("Inchiriere");
        QPushButton* button_sort_pret = new QPushButton("Sortare pret");
        QPushButton* button_sort_marime = new QPushButton("Sortare marime");

    public:
    GUI(Service& service) : service(service) {
        init_GUI();
        load_data();
        init_connections();
    }

    void load_data();

    void init_GUI();

    void init_connections();
};
