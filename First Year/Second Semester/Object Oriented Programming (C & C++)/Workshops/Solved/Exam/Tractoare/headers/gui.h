#pragma once
#include "service.h"
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

class Gui : public QWidget {
public:
    Gui(Service& service) : service(service) {
        load_data();
        init_gui();
        init_signals();
    }

private:
    Service& service;

    QTableView* table = new QTableView();
    QPushButton* addButton = new QPushButton("Adauga");
    QLineEdit* id_field = new QLineEdit();
    QLineEdit* denumire_field = new QLineEdit();
    QLineEdit* tip_field = new QLineEdit();
    QLineEdit* numarRoti_field = new QLineEdit();

    QComboBox* combobox = new QComboBox();

    void load_data();

    void init_gui();

    void init_signals();
};
