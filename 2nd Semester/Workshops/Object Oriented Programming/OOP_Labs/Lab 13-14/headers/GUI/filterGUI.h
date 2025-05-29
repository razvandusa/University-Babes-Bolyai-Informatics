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

class FiltreazaWindow : public QWidget {
public:
    FiltreazaWindow(Service& serv) : service(serv) {
        init_GUI();
        init_connections();
    }
private:

    Service& service;
    QListWidget* lista_filtrata_GUI = new QListWidget();

    QLineEdit* ore_GUI = new QLineEdit();
    QLineEdit* cadru_didactic_GUI = new QLineEdit();

    QPushButton* numar_ore_button = new QPushButton("&Numar Ore");
    QPushButton* cadru_didactic_button = new QPushButton("&Cadru Didactic");

    /**
     * Incarca lista de discipline filtrata in widgetul grafic.
     * @param lista_discipline Vector de obiecte Disciplina.
     */
    void load_data(std::vector<Disciplina>& lista_discipline) const;

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