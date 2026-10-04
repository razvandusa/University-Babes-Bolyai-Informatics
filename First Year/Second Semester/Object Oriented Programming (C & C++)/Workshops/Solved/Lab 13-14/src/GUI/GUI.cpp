#include "../headers/GUI/GUI.h"
#include "../headers/GUI/contractCrudGUI.h"
#include "../headers/GUI/contractReadOnlyGUI.h"
#include "../headers/GUI/sortGUI.h"
#include "../headers/GUI/filterGUI.h"
#include "modelView.h"
#include <iostream>

void GUI::load_data() {
    lista_GUI->clear();
    tabel_model->updateDiscipline({});
    std::vector<Disciplina>& lista_discipline = service.get_lista_discipline();
    int row = 0;
    for (const auto& disciplina : lista_discipline) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(disciplina.get_denumire()));
        item->setData(Qt::UserRole, disciplina.get_id());
        item->setData(Qt::UserRole + 1, QString::fromStdString(disciplina.get_denumire()));
        item->setData(Qt::UserRole + 2, disciplina.get_ore());
        item->setData(Qt::UserRole + 3, QString::fromStdString(disciplina.get_tip()));
        item->setData(Qt::UserRole + 4, QString::fromStdString(disciplina.get_cadru_didactic()));
        if (disciplina.get_tip() == "Obligatorie") {
            item->setData(Qt::BackgroundRole,QBrush(Qt::red, Qt::SolidPattern));
        }
        lista_GUI->addItem(item);
    }
    tabel_model->updateDiscipline(service.get_lista_discipline());
}

void GUI::init_GUI() {
    QHBoxLayout *mainLayout = new QHBoxLayout();
    tabel_GUI->setModel(tabel_model);

    QHBoxLayout *listAndTableLayout = new QHBoxLayout();
    listAndTableLayout->addWidget(lista_GUI);
    listAndTableLayout->addWidget(tabel_GUI);
    mainLayout->addLayout(listAndTableLayout);

    QVBoxLayout *secondLayout = new QVBoxLayout();

    QFormLayout *disciplinaLayout = new QFormLayout();
    disciplinaLayout->addRow("Id",id_GUI);
    disciplinaLayout->addRow("Denumire",denumire_GUI);
    disciplinaLayout->addRow("Ore",ore_GUI);
    disciplinaLayout->addRow("Tip",tip_GUI);
    disciplinaLayout->addRow("Cadru didactic",cadru_didactic_GUI);
    secondLayout->addLayout(disciplinaLayout);

    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(adauga_button);
    buttonLayout->addWidget(sterge_button);
    buttonLayout->addWidget(modifica_button);
    buttonLayout->addWidget(undo_button);
    buttonLayout->addWidget(sort_button);
    buttonLayout->addWidget(filtreaza_button);
    buttonLayout->addWidget(contract_button);
    buttonLayout->addWidget(exit_button);
    buttonLayout->addWidget(btnCRUD);
    buttonLayout->addWidget(btnReadOnly);
    secondLayout->addLayout(buttonLayout);

    mainLayout->addLayout(secondLayout);
    setLayout(mainLayout);
    setWindowTitle("Aplicatie");
    show();
}

void GUI::init_connections() {
    QObject::connect(exit_button, &QPushButton::clicked,[&]() {
       close();
    });

    QObject::connect(adauga_button, &QPushButton::clicked,[&]() {
        auto id_string = id_GUI->text().toStdString();
        int id;
        try {
            id = Validator::conversie_valida(id_string);
        } catch (const NotValid& e) {
            clear_line_edits();
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
            return;
        }
        auto denumire = denumire_GUI->text().toStdString();
        auto ore_string = ore_GUI->text().toStdString();
        int ore;
        try {
            ore = Validator::conversie_valida(ore_string);
        } catch (const NotValid& e) {
            clear_line_edits();
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
            return;
        }
        auto tip = tip_GUI->text().toStdString();
        auto cadru_didactic = cadru_didactic_GUI->text().toStdString();
        try {
            clear_line_edits();
            service.add_disciplina(id, denumire, ore, tip, cadru_didactic);
            load_data();
        } catch (const NotValid& e) {
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
        } catch (const AlreadyExisting& e) {
            QMessageBox::information(nullptr,"AlreadyExisting",QString::fromStdString(e.get_message()));
        }
    });

    QObject::connect(sterge_button, &QPushButton::clicked,[&]() {
        auto id_string = id_GUI->text().toStdString();
        int id;
        try {
            id = Validator::conversie_valida(id_string);
        } catch (const NotValid& e) {
            clear_line_edits();
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
            return;
        }
        try {
            clear_line_edits();
            service.remove_disciplina(id);
            load_data();
        } catch (const NotExisting& e) {
            QMessageBox::information(nullptr,"NotExisting",QString::fromStdString(e.get_message()));
        }
    });

    QObject::connect(modifica_button, &QPushButton::clicked,[&]() {
        auto id_string = id_GUI->text().toStdString();
        int id;
        try {
            id = Validator::conversie_valida(id_string);
        } catch (const NotValid& e) {
            clear_line_edits();
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
            return;
        }
        auto new_denumire = denumire_GUI->text().toStdString();
        auto ore_string = ore_GUI->text().toStdString();
        int new_ore;
        try {
            new_ore = Validator::conversie_valida(ore_string);
        } catch (const NotValid& e) {
            clear_line_edits();
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
            return;
        }
        auto new_tip = tip_GUI->text().toStdString();
        auto new_cadru_didactic = cadru_didactic_GUI->text().toStdString();
        try {
            clear_line_edits();
            service.update_disciplina(id, new_denumire, new_ore, new_tip, new_cadru_didactic);
            load_data();
        } catch (const NotValid& e) {
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
        } catch (const NotExisting& e) {
            QMessageBox::information(nullptr,"NotExisting",QString::fromStdString(e.get_message()));
        }
    });

    QObject::connect(undo_button, &QPushButton::clicked,[&]() {
        try {
            service.undo();
            load_data();
        } catch (const std::runtime_error& e) {
            QMessageBox::information(nullptr,"EmptyList",e.what());
        }
    });

    QObject::connect(sort_button, &QPushButton::clicked,[&]() {
        auto* sort_window = new SortWindow (service, this);
        sort_window->show();
    });

    QObject::connect(filtreaza_button, &QPushButton::clicked,[&]() {
        auto* filtreaza_window = new FiltreazaWindow(service);
        filtreaza_window->show();
    });

    QObject::connect(contract_button, &QPushButton::clicked,[&]() {
        contract_window = new ContractGUI(service, contract);
        contract_window->show();
    });

    QObject::connect(btnCRUD, &QPushButton::clicked,[&]() {
        if (contract_window != nullptr) {
            auto *contract_CRUD = new ContractCrudGUI(service, contract);
            contract_window->addObserver(contract_CRUD);
            contract_window->notifyObservers();
            contract_CRUD->show();
        } else {
            QMessageBox::information(nullptr,"NotExisting","Mai intai trebuie deschisa fereastra contract!");
        }
    });

    QObject::connect(btnReadOnly, &QPushButton::clicked,[&]() {
        if (contract_window != nullptr) {
            auto *contract_ReadOnly = new ContractReadOnlyGUI(contract);
            contract_window->addObserver(contract_ReadOnly);
            contract_window->notifyObservers();
            contract_ReadOnly->show();
        } else {
            QMessageBox::information(nullptr,"NotExisting","Mai intai trebuie deschisa fereastra contract!");
        }
    });

    QObject::connect(lista_GUI, &QListWidget::itemSelectionChanged,[&]() {
        auto sel = lista_GUI->selectedItems();
        if (sel.empty()) {
            id_GUI->setText("");
            denumire_GUI->setText("");
            ore_GUI->setText("");
            tip_GUI->setText("");
            cadru_didactic_GUI->setText("");
        } else {
            auto selItem = sel.at(0);
            id_GUI->setText(selItem->data(Qt::UserRole).toString());
            denumire_GUI->setText(selItem->data(Qt::UserRole + 1).toString());
            ore_GUI->setText(selItem->data(Qt::UserRole + 2).toString());
            tip_GUI->setText(selItem->data(Qt::UserRole + 3).toString());
            cadru_didactic_GUI->setText(selItem->data(Qt::UserRole + 4).toString());
        }
    });
}

void GUI::clear_line_edits() {
    id_GUI->clear();
    denumire_GUI->clear();
    ore_GUI->clear();
    tip_GUI->clear();
    cadru_didactic_GUI->clear();
}