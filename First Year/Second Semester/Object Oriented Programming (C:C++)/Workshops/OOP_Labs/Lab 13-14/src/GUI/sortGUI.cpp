#include "../headers/GUI/sortGUI.h"
void SortWindow::init_GUI() {
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(denumire_button);
    buttonLayout->addWidget(numar_ore_button);
    buttonLayout->addWidget(cadru_didactic_button);
    buttonLayout->addWidget(tip_button);

    setLayout(buttonLayout);
    setWindowTitle("Sortare");
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