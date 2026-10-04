#pragma once
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QWidget>
#include "observer.h"
#include "service.h"

class Gui : public QWidget {
public:
    Gui(Service &service) : service(service) {
        load_data();
        init_gui();
        init_signals();
    }

private:
    Service service;
    QTableView *table = new QTableView();

    /**
     * Functia incarca lista de produse din service in tabel
     */
    void load_data();

    /**
     * Functia initializeaza gui-ul ferestrei
     */
    void init_gui();

    /**
     * Functia initializeaza semnalele
     */
    void init_signals();

    QLineEdit *id_field = new QLineEdit();
    QLineEdit *nume_field = new QLineEdit();
    QLineEdit *tip_field = new QLineEdit();
    QLineEdit *pret_field = new QLineEdit();
    QPushButton *buttonAdd = new QPushButton("Add");
    QSlider *slider = new QSlider();
    QLabel* sliderValue = new QLabel("Value : 0");
};

class WindowTip : public QWidget, public Observer {
public:
    WindowTip(std::string tip, int count) : tip(tip), count(count) {
        init_gui();
        show();
    }

    /**
     * Functia initializeaza gui-ul ferestrei
     */
    void init_gui();

    /**
     * Functia da update produselor cu tipul precizat
     * @param tip tipul a caror produse vrem sa se updateze
     */
    void update(std::string tip) override;

private:
    std::string tip;
    int count;
    QLabel *label = new QLabel();
};