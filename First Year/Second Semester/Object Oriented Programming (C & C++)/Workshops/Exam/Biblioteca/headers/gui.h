#pragma once
#include "../headers/domain.h"
#include <QPushButton>
#include "service.h"
#include "QMessageBox"
#include "QLineEdit"
#include "QListWidget"
#include "QHBoxLayout"
#include "QTextEdit"

class GUI : public QWidget {
    private:
        Service& service;
        QListWidget* lista_gui = new QListWidget();
        std::vector<Carte> lista_carti = service.get_all();
        QPushButton* button_sort_titlu = new QPushButton("Sortare titlu");
        QPushButton* button_filtrare_gen = new QPushButton("Filtrare gen");
        QPushButton* button_resetare = new QPushButton("Resetare");
        QLineEdit* edit_filtrare = new QLineEdit();
        QTextEdit* bloc = new QTextEdit();

    public:
    /*
     *  Creeaza un gui cu referinta la service
     *  service : Service
     */
    GUI(Service& service) : service(service) {
        init_GUI();
        load_data();
        init_connections();
    }

    /*
     *  Incarca datele in lista gui
     */
    void load_data();

    /*
     *  Initializeaza interfata grafica
     */
    void init_GUI();

    /*
     *  Initializeaza conexiunile
     */
    void init_connections();
};
