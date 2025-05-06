#include "../headers/disciplineGUI.h"

void DisciplineGUI::load_data() {
    lista_GUI->clear();
    std::vector<Disciplina>& lista_discipline = service.get_lista_discipline();
    for (const auto& disciplina : lista_discipline) {
        QString line = QString::fromStdString(
            std::to_string(disciplina.get_id()) + " | " +
            disciplina.get_denumire() + " | " +
            std::to_string(disciplina.get_ore()) + " | " +
            disciplina.get_tip() + " | " +
            disciplina.get_cadru_didactic()
        );
        lista_GUI->addItem(line);
    }
}

void DisciplineGUI::init_GUI() {
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(lista_GUI);

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
}

void DisciplineGUI::clear_line_edits() {
    id_GUI->clear();
    denumire_GUI->clear();
    ore_GUI->clear();
    tip_GUI->clear();
    cadru_didactic_GUI->clear();
}