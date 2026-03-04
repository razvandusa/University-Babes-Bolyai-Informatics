#pragma once
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPainter>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>
#include <vector>
#include <string>
#include "contractCrud.h"
#include "contract.h"
#include "service.h"
#include "GUI.h"

class SortWindow : public QWidget {
public:
    SortWindow(Service& serv, GUI* ptr) : service(serv), main_window_ptr(ptr) {
        init_GUI();
        init_connections();
    }

private:
    Service& service;
    GUI* main_window_ptr;
    QPushButton* denumire_button = new QPushButton("&Denumire");
    QPushButton* numar_ore_button = new QPushButton("&Numar Ore");
    QPushButton* cadru_didactic_button = new QPushButton("&Cadru Didactic");
    QPushButton* tip_button = new QPushButton("&Tip");

    /**
     * Initializeaza si aranjeaza elementele vizuale ale interfetei grafice.
     */
    void init_GUI();

    /**
     * Creeaza conexiunile (signal-slot) pentru butoanele interfetei.
     */
    void init_connections();
};