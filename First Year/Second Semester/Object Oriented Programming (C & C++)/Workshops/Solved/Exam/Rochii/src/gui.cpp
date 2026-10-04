#include "../headers/gui.h"
#include "QMessageBox"
#include "QListWidget"
#include "QHBoxLayout"

void GUI::load_data() {
        lista_gui->clear();
        for (auto& rochie : service.get_all()) {
            QString text = QString::fromStdString(
                std::to_string(rochie.get_cod()) + " | " +
                rochie.get_denumire() + " | " +
                rochie.get_marime() + " | " +
                std::to_string(rochie.get_pret()) + " | " +
                rochie.get_disponibilitate()
            );
            QListWidgetItem* item = new QListWidgetItem(text);
            if (rochie.get_disponibilitate() == "False") {
                item->setBackground(QBrush(Qt::red));
            } else {
                item->setBackground(QBrush(Qt::green));
            }
            lista_gui->addItem(item);
        }
    }

void GUI::init_GUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout();
    QHBoxLayout* listLayout = new QHBoxLayout();
    QHBoxLayout* butoaneLayout = new QHBoxLayout();

    lista_gui = new QListWidget();
    listLayout->addWidget(lista_gui);

    butoaneLayout->addWidget(button_inchiriere);
    butoaneLayout->addWidget(button_sort_pret);
    butoaneLayout->addWidget(button_sort_marime);

    mainLayout->addLayout(listLayout);
    mainLayout->addLayout(butoaneLayout);
    setLayout(mainLayout);
    show();
}

void GUI::init_connections() {
    QObject::connect(button_sort_marime, &QPushButton::clicked,[&]() {
    service.sortare_marime();
    load_data();
    });

    QObject::connect(button_sort_pret, &QPushButton::clicked,[&]() {
    service.sortare_pret();
    load_data();
    });

    QObject::connect(button_inchiriere, &QPushButton::clicked,[&]() {
        QListWidgetItem* selectedItem = lista_gui->currentItem();
        if (!selectedItem) {
            return;
        }

        QString text = selectedItem->text();
        QStringList parts = text.split(" | ");
        int cod = std::stoi(parts[0].toStdString());
        std::string disponibilitate = parts[4].toStdString();
        qDebug() << "disponibilitate: " << disponibilitate;
        if (disponibilitate == "True") {
            service.inchiriaza(cod);
            load_data();
        } else {
            QMessageBox::information(nullptr,"Information","Rochia nu este disponibila!");
        }
    });
}