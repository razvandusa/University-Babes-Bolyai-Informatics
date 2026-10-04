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

class ContractReadOnlyGUI : public QWidget, public Observer {
public:
    ContractReadOnlyGUI(Contract& cont) : contract(cont) {
        init_GUI();
    }

    /**
     * Reincarca afisajul grafic pe baza continutului contractului.
     */
    void update() override;

private:
    Contract& contract;

    void paintEvent(QPaintEvent* event) override;

    /*
     *  Functia init_GUI creeaza si aranjeaza elementele vizuale lae interfetei grafice
     */
    void init_GUI();
};