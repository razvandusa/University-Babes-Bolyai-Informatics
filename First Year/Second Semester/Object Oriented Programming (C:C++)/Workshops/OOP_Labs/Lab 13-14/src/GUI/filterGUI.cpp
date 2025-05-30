#include "../headers/GUI/filterGUI.h"
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
    setWindowTitle("Filtrare");
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