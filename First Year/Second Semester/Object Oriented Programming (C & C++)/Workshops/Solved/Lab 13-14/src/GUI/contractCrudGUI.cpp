#include "../headers/GUI/contractCrudGUI.h"

void ContractCrudGUI::clear_line_edits() {
    id_GUI->clear();
    numar_contracte_generat_GUI->clear();
}

void ContractCrudGUI::load_data(const std::vector<Disciplina>& lista_discipline) const {
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

void ContractCrudGUI::update() {
    qDebug() << "update() called in ContractCrudGUI";
    std::vector<Disciplina>& lista_discipline = contract.get_lista_discipline_contract();
    contractCrud.reload_contract(lista_discipline);
    load_data(lista_discipline);
}

void ContractCrudGUI::init_GUI() {
    QHBoxLayout *filtreazaLayout = new QHBoxLayout();
    filtreazaLayout->addWidget(lista_contract_GUI);

    QVBoxLayout *secondLayout = new QVBoxLayout();

    QFormLayout *textLayout = new QFormLayout();
    textLayout->addRow("Id",id_GUI);
    textLayout->addRow("Numarul de contracte (generare)",numar_contracte_generat_GUI);
    secondLayout->addLayout(textLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(adauga_button);
    buttonLayout->addWidget(goleste_contract);
    buttonLayout->addWidget(generare_button);
    buttonLayout->addWidget(exit_button);
    secondLayout->addLayout(buttonLayout);

    filtreazaLayout->addLayout(secondLayout);
    setLayout(filtreazaLayout);
    setWindowTitle("Contract CRUD");
    show();
}

void ContractCrudGUI::init_connections() {
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