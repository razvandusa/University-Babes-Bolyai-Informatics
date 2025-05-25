#include "../headers/gui.h"
void GUI::load_data() {
    lista_gui->clear();
    for (auto& c : service.get_all()) {
        QString text = QString::fromStdString(
            std::to_string(c.get_id()) + " | " +
            std::to_string(c.get_cod()) + " | " +
            c.get_titlu() + " | " +
            c.get_autor() + " | " +
            c.get_gen()
        );
        QListWidgetItem* item = new QListWidgetItem(text);
        if (c.get_gen() == "roman") {
            item->setBackground(QBrush(Qt::lightGray));
        } else if (c.get_gen() == "poezie") {
            item->setBackground(QBrush(Qt::darkGreen));
        } else if (c.get_gen() == "eseu") {
            item->setBackground(QBrush(Qt::blue));
        } else if (c.get_gen() == "thriller") {
            item->setBackground(QBrush(Qt::red));
        }
        lista_gui->addItem(item);
    }
}

void GUI::init_GUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout();
    QHBoxLayout* listLayout = new QHBoxLayout();
    QHBoxLayout* butoaneLayout = new QHBoxLayout();

    listLayout->addWidget(lista_gui);
    listLayout->addWidget(bloc);
    bloc->setReadOnly(true);

    butoaneLayout->addWidget(button_sort_titlu);
    butoaneLayout->addWidget(edit_filtrare);
    butoaneLayout->addWidget(button_filtrare_gen);
    butoaneLayout->addWidget(button_resetare);

    mainLayout->addLayout(listLayout);
    mainLayout->addLayout(butoaneLayout);
    setLayout(mainLayout);
    show();
}

void GUI::init_connections(){
    QObject::connect(button_sort_titlu, &QPushButton::clicked,[&]() {
    service.sortare_titlu();
    load_data();
    });

    QObject::connect(button_resetare, &QPushButton::clicked,[&]() {
        service.get_all() = lista_carti;
        load_data();
    });

    QObject::connect(button_filtrare_gen, &QPushButton::clicked,[&]() {
    std::string criteriu = edit_filtrare->text().toStdString();
    if (criteriu != "roman" && criteriu != "poezie" && criteriu != "eseu" && criteriu != "thriller") {
        QMessageBox::information(nullptr,"Information","Singurele campuri pentru filtrare sunt roman, poezie, eseu si thriller!");
        return ;
    } else {
        std::vector<Carte> lista_filtrata = service.filtrare_gen(criteriu);
        lista_gui->clear();
        for (auto& c : lista_filtrata) {
            QString text = QString::fromStdString(
                std::to_string(c.get_id()) + " | " +
                std::to_string(c.get_cod()) + " | " +
                c.get_titlu() + " | " +
                c.get_autor() + " | " +
                c.get_gen()
            );
            QListWidgetItem* item = new QListWidgetItem(text);
            if (c.get_gen() == "roman") {
                item->setBackground(QBrush(Qt::lightGray));
            } else if (c.get_gen() == "poezie") {
                item->setBackground(QBrush(Qt::darkGreen));
            } else if (c.get_gen() == "eseu") {
                item->setBackground(QBrush(Qt::blue));
            } else if (c.get_gen() == "thriller") {
                item->setBackground(QBrush(Qt::red));
            }
            lista_gui->addItem(item);
        }
    }
    });

    QObject::connect(lista_gui, &QListWidget::itemSelectionChanged, [&]() {
        QListWidgetItem* selectedItem = lista_gui->currentItem();
        if (!selectedItem) {
            bloc->clear();
            return;
        }
        QStringList parts = selectedItem->text().split(" | ");
        QString mesaj = parts[2] + " este o carte scrisa de " + parts[3] + " si face parte din genul " + parts[4];
        bloc->setText(mesaj);
    });
}