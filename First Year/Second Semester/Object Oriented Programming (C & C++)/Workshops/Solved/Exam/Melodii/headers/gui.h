#pragma once
#include <QPushButton>
#include <QWidget>
#include <QTableView>
#include <QLineEdit>

#include "observer.h"
#include "service.h"

class Gui : public QWidget , public Subject {
public:
    Gui(Service service) : service(std::move(service)){
        load_data();
        init_gui();
        init_signal();
    }

private:
    void load_data();

    void init_gui();

    void init_signal();

    QTableView* table = new QTableView();
    QPushButton* buttonUpdate = new QPushButton("Update");
    QPushButton* buttonDelete = new QPushButton("Delete");
    QLineEdit* melodieTitle = new QLineEdit();
    QSlider* melodieRank = new QSlider();
    int id_selected = 0;

    Service service;
};

class Paint : public QWidget, public Observer {
public:
    Paint(Service& service) : service(service) {}

private:
    void paintEvent(QPaintEvent *event) override;

    void update() override {
        repaint();
    }

    Service& service;
};