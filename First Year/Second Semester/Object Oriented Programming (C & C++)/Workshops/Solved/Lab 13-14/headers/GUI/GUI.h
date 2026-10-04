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
#include "contractGUI.h"
#include "modelView.h"

class GUI : public QWidget {
public:
    GUI(Service& serv) : service(serv) {
        init_GUI();
        load_data();
        init_connections();
    }

    /**
     * Incarca lista de discipline din service in widgetul grafic.
     */
    void load_data();

private:
    Contract contract;
    Service& service;
    ContractGUI *contract_window = nullptr;
    QListWidget* lista_GUI = new QListWidget();
    QTableView* tabel_GUI = new QTableView();
    TabelModel* tabel_model = new TabelModel({});

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

    QPushButton* btnCRUD = new QPushButton("CRUD Contract");
    QPushButton* btnReadOnly = new QPushButton("ReadOnly Contract");

    /**
     * Initializeaza si aranjeaza elementele vizuale ale interfetei grafice.
     */
    void init_GUI();

    /**
     * Creeaza conexiunile (signal-slot) pentru butoanele interfetei.
     */
    void init_connections();

    /**
     * Sterge textul din campurile de editare.
     */
    void clear_line_edits();
};