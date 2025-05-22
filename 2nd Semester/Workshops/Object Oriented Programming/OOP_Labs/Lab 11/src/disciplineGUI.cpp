#include "../headers/disciplineGUI.h"

#include <iostream>

void DisciplineGUI::load_data() {
    lista_GUI->clear();
    tabel_GUI->clear();
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

        tabel_GUI->insertRow(row);
        tabel_GUI->setItem(row, 0, new QTableWidgetItem(QString::number(disciplina.get_id())));
        tabel_GUI->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(disciplina.get_denumire())));
        tabel_GUI->setItem(row, 2, new QTableWidgetItem(QString::number(disciplina.get_ore())));
        tabel_GUI->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(disciplina.get_tip())));
        tabel_GUI->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(disciplina.get_cadru_didactic())));

        if (disciplina.get_tip() == "Obligatorie") {
            for (int col = 0; col < 5; col++) {
                tabel_GUI->item(row, col)->setBackground(QBrush(Qt::red, Qt::SolidPattern));
            }
        }
    }
}

void DisciplineGUI::init_GUI() {
    QHBoxLayout *mainLayout = new QHBoxLayout();
    tabel_GUI->setColumnCount(5);  // Id, Denumire, Ore, Tip, Cadru Didactic
    tabel_GUI->setHorizontalHeaderLabels({"Id", "Denumire", "Ore", "Tip", "Cadru Didactic"});

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

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(adauga_button);
    buttonLayout->addWidget(sterge_button);
    buttonLayout->addWidget(modifica_button);
    buttonLayout->addWidget(undo_button);
    buttonLayout->addWidget(sort_button);
    buttonLayout->addWidget(filtreaza_button);
    buttonLayout->addWidget(contract_button);
    buttonLayout->addWidget(exit_button);
    secondLayout->addLayout(buttonLayout);

    mainLayout->addLayout(secondLayout);
    setLayout(mainLayout);
    show();
}

void DisciplineGUI::init_connections() {
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
        auto *contract_window = new ContractGUI(service);
        contract_window->show();
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

void DisciplineGUI::clear_line_edits() {
    id_GUI->clear();
    denumire_GUI->clear();
    ore_GUI->clear();
    tip_GUI->clear();
    cadru_didactic_GUI->clear();
}

void SortWindow::init_GUI() {
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(denumire_button);
    buttonLayout->addWidget(numar_ore_button);
    buttonLayout->addWidget(cadru_didactic_button);
    buttonLayout->addWidget(tip_button);

    setLayout(buttonLayout);
    show();
}

void SortWindow::init_connections() {
    QObject::connect(denumire_button, &QPushButton::clicked,[this]() {
       Service::sortare_discipline(service.get_lista_discipline(), "denumire");
        main_window_ptr->load_data();
    });

    QObject::connect(numar_ore_button, &QPushButton::clicked,[this]() {
       Service::sortare_discipline(service.get_lista_discipline(), "numar ore");
        main_window_ptr->load_data();
    });

    QObject::connect(cadru_didactic_button, &QPushButton::clicked,[this]() {
       Service::sortare_discipline(service.get_lista_discipline(), "cadru didactic");
        main_window_ptr->load_data();
    });

    QObject::connect(tip_button, &QPushButton::clicked,[this]() {
       Service::sortare_discipline(service.get_lista_discipline(), "tip");
        main_window_ptr->load_data();
    });
}

void FiltreazaWindow::clear_line_edits() {
    ore_GUI->clear();
    cadru_didactic_GUI->clear();
}

void FiltreazaWindow::load_data(std::vector<Disciplina>& lista_discipline) const {
    lista_filtrata_GUI->clear();
    for (const auto& disciplina : lista_discipline) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(disciplina.get_denumire()));
        item->setData(Qt::UserRole + 2, disciplina.get_ore());
        item->setData(Qt::UserRole + 4, QString::fromStdString(disciplina.get_cadru_didactic()));
        if (disciplina.get_tip() == "Obligatorie") {
            item->setData(Qt::BackgroundRole,QBrush(Qt::red, Qt::SolidPattern));
        }
        lista_filtrata_GUI->addItem(item);
    }
}

void FiltreazaWindow::init_GUI() {
    QHBoxLayout *filtreazaLayout = new QHBoxLayout();
    std::vector<Disciplina>& lista_discipline = service.get_lista_discipline();
    load_data(lista_discipline);
    filtreazaLayout->addWidget(lista_filtrata_GUI);

    QVBoxLayout *secondLayout = new QVBoxLayout();

    QFormLayout *textLayout = new QFormLayout();
    textLayout->addRow("Numar minim de ore",ore_GUI);
    textLayout->addRow("Numele cadrului didactic",cadru_didactic_GUI);
    secondLayout->addLayout(textLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(numar_ore_button);
    buttonLayout->addWidget(cadru_didactic_button);
    secondLayout->addLayout(buttonLayout);

    filtreazaLayout->addLayout(secondLayout);
    setLayout(filtreazaLayout);
    show();
}

void FiltreazaWindow::init_connections() {

    QObject::connect(numar_ore_button, &QPushButton::clicked,[this]() {
        auto ore_string = ore_GUI->text().toStdString();
        try {
            int ore = Validator::conversie_valida(ore_string);
        } catch (const NotValid& e) {
            clear_line_edits();
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
            return;
        }
        auto lista_filtrata =  Service::filtrare_discipline(service.get_lista_discipline(), "numar ore",ore_string);
        load_data(lista_filtrata);
    });

    QObject::connect(cadru_didactic_button, &QPushButton::clicked,[this]() {
        auto cadru_didactic = cadru_didactic_GUI->text().toStdString();
        auto lista_filtrata = Service::filtrare_discipline(service.get_lista_discipline(), "cadru didactic", cadru_didactic);
        load_data(lista_filtrata);
    });

    QObject::connect(lista_filtrata_GUI, &QListWidget::itemSelectionChanged,[&]() {
        auto sel = lista_filtrata_GUI->selectedItems();
        if (sel.empty()) {
            ore_GUI->setText("");
            cadru_didactic_GUI->setText("");
        } else {
            auto selItem = sel.at(0);
            ore_GUI->setText(selItem->data(Qt::UserRole + 2).toString());
            cadru_didactic_GUI->setText(selItem->data(Qt::UserRole + 4).toString());
        }
    });

}

void ContractGUI::clear_line_edits() {
    id_GUI->clear();
    numar_contracte_generat_GUI->clear();
    export_contracte_GUI->clear();
}

void ContractGUI::load_data(const std::vector<Disciplina>& lista_discipline) const {
    lista_contract_GUI->clear();
    for (const auto& disciplina : lista_discipline) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(disciplina.get_denumire()));
        item->setData(Qt::UserRole, disciplina.get_id());
        if (disciplina.get_tip() == "Obligatorie") {
            item->setData(Qt::BackgroundRole,QBrush(Qt::red, Qt::SolidPattern));
        }
        lista_contract_GUI->addItem(item);
    }
}

void ContractGUI::init_GUI() {
    QHBoxLayout *filtreazaLayout = new QHBoxLayout();
    filtreazaLayout->addWidget(lista_contract_GUI);

    QVBoxLayout *secondLayout = new QVBoxLayout();

    QFormLayout *textLayout = new QFormLayout();
    textLayout->addRow("Id",id_GUI);
    textLayout->addRow("Numarul de contracte (generare)",numar_contracte_generat_GUI);
    textLayout->addRow("Numele fisierului (export)",export_contracte_GUI);
    secondLayout->addLayout(textLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(adauga_button);
    buttonLayout->addWidget(goleste_contract);
    buttonLayout->addWidget(generare_button);
    buttonLayout->addWidget(exporta_button);
    buttonLayout->addWidget(exit_button);
    secondLayout->addLayout(buttonLayout);

    filtreazaLayout->addLayout(secondLayout);
    setLayout(filtreazaLayout);
    show();
}

void ContractGUI::init_connections() {
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
        try {
            clear_line_edits();
            contract.add_disciplina_contract(id, service);
            load_data(contract.get_lista_discipline_contract());
        } catch (const NotValid& e) {
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
        } catch (const AlreadyExisting& e) {
            QMessageBox::information(nullptr,"AlreadyExisting",QString::fromStdString(e.get_message()));
        } catch (const NotExisting& e) {
            QMessageBox::information(nullptr,"NotExisting",QString::fromStdString(e.get_message()));
        }
    });

    QObject::connect(generare_button, &QPushButton::clicked,[&]() {
        std::string number_to_generate_string = numar_contracte_generat_GUI->text().toStdString();
        int number_to_generate;
        try {
            number_to_generate = Validator::conversie_valida(number_to_generate_string);
        } catch (const NotValid& e) {
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
            return;
        }
        try {
            contract.generate_contract(number_to_generate,service);
            load_data(contract.get_lista_discipline_contract());
        } catch (const NotExisting& e) {
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
        } catch (const NotValid& e) {
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
        }
    });

    QObject::connect(exporta_button, &QPushButton::clicked,[&]() {
        std::string file_name = export_contracte_GUI->text().toStdString();
        try {
            contract.export_contract(file_name);
            QMessageBox::information(nullptr,"Information","Exportul a fost finalizat cu succes!");
        } catch (const NotValid& e) {
            QMessageBox::information(nullptr,"NotValid",QString::fromStdString(e.get_message()));
        }
    });

    QObject::connect(goleste_contract, &QPushButton::clicked,[&]() {
        std::vector<Disciplina> empty_vector;
        load_data(empty_vector);
    });

    QObject::connect(lista_contract_GUI, &QListWidget::itemSelectionChanged,[&]() {
        auto sel = lista_contract_GUI->selectedItems();
        if (sel.empty()) {
            id_GUI->setText("");
        } else {
            auto selItem = sel.at(0);
            id_GUI->setText(selItem->data(Qt::UserRole).toString());
        }
    });
}