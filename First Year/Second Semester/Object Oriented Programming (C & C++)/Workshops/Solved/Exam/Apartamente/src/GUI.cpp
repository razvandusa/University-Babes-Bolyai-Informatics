#include "../headers/GUI.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFormLayout>

void GUI::load_data() {
    auto lista_apartamente = service.get_all();
    lista_gui->clear();
    for (const Apartament& ap : lista_apartamente) {
        QString itemText = QString::fromStdString(
        std::to_string(ap.get_id()) + " | " +
        ap.get_strada() + " | " +
        ap.get_suprafata() + " | " +
        std::to_string(ap.get_pret())
        );
        lista_gui->addItem(itemText);
    }
}

void GUI::init_GUI() {
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QHBoxLayout *listLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QFormLayout *lineEditLayout = new QFormLayout();

    lista_gui = new QListWidget;
    listLayout->addWidget(lista_gui);
    mainLayout->addLayout(listLayout);

    buttonLayout->addWidget(button_sterge);
    buttonLayout->addWidget(button_filtreaza_suprafata);
    buttonLayout->addWidget(button_filtreaza_pret);
    mainLayout->addLayout(buttonLayout);

    lineEditLayout->addRow("Min",line_edit_min);
    lineEditLayout->addRow("Max",line_edit_max);
    mainLayout->addLayout(lineEditLayout);

    setLayout(mainLayout);
}

void GUI::init_connections() {
    QObject::connect(button_sterge, &QPushButton::clicked,[&]() {
        QListWidgetItem* selectedItem = lista_gui->currentItem();
        if (!selectedItem) {
            return;
        }

        QString text = selectedItem->text();
        QStringList parts = text.split("|");
        int id = parts[0].toInt();
        service.delete_apartament_service(id);
        load_data();
    });

    QObject::connect(button_filtreaza_pret, &QPushButton::clicked, [&]() {
        std::vector<Apartament> lista_filtrata;
        try {
            lista_filtrata = service.filtreaza_pret(line_edit_min->text().toStdString(), line_edit_max->text().toStdString());
        } catch (...) {
            QMessageBox::information(nullptr,"Information","Min sau max trebuie sa fie numere intregi!");
            return ;
        }

        lista_gui->clear();
        for (const Apartament& ap : lista_filtrata) {
            QString itemText = QString::fromStdString(
                std::to_string(ap.get_id()) + " | " +
                ap.get_strada() + " | " +
                ap.get_suprafata() + " | " +
                std::to_string(ap.get_pret())
            );
            lista_gui->addItem(itemText);
        }
    });

    QObject::connect(button_filtreaza_suprafata, &QPushButton::clicked, [&]() {
       std::vector<Apartament> lista_filtrata;
        try {
            lista_filtrata = service.filtreaza_suprafata(line_edit_min->text().toStdString(), line_edit_max->text().toStdString());
        } catch (...) {
            QMessageBox::information(nullptr,"Information","Min sau max trebuie sa fie numere intregi!");
            return ;
        }

        lista_gui->clear();
        for (const Apartament& ap : lista_filtrata) {
            QString itemText = QString::fromStdString(
                std::to_string(ap.get_id()) + " | " +
                ap.get_strada() + " | " +
                ap.get_suprafata() + " | " +
                std::to_string(ap.get_pret())
            );
            lista_gui->addItem(itemText);
        }
    });
}