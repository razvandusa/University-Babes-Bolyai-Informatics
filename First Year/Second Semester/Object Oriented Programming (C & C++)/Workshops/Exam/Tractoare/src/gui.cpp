#include "../headers/gui.h"
#include <QStandardItemModel>
#include <QLabel>
#include <set>
#include <QHBoxLayout>
#include <QMessageBox>

void Gui::load_data() {
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"id", "denumire", "tip", "numarRoti", "numar tractoare de acelasi tip"});
    model->setColumnCount(5);

    int rowCount = 0;
    auto& lista_tractoare = service.get_all();
    std::set<std::string> tipuri;
    sort(lista_tractoare.begin(), lista_tractoare.end(), [](const Tractor& a, const Tractor& b) { return a.get_denumire() > b.get_denumire(); });
    for (auto& tractor : lista_tractoare) {
        QStandardItem* id = new QStandardItem(QString::number(tractor.get_id()));
        QStandardItem* denumire = new QStandardItem(QString::fromStdString(tractor.get_denumire()));
        QStandardItem* tip = new QStandardItem(QString::fromStdString(tractor.get_tip()));
        QStandardItem* numarRoti = new QStandardItem(QString::number(tractor.get_numarRoti()));
        QStandardItem* numarTractoareAcelasiTip = new QStandardItem(QString::number(service.numarTractoareAcelasiTip(tractor.get_tip())));

        if (tipuri.find(tractor.get_tip()) == tipuri.end()) {
            combobox->addItem(QString::fromStdString(tractor.get_tip()));
        }
        tipuri.insert(tractor.get_tip());

        model->insertRow(rowCount, {id, denumire, tip, numarRoti, numarTractoareAcelasiTip});
    }



    service.write_to_file();
    table->setModel(model);
}

void Gui::init_gui() {
    QHBoxLayout* mainLayout = new QHBoxLayout();
    QVBoxLayout* tableLayout = new QVBoxLayout();
    QVBoxLayout* addLayout = new QVBoxLayout();
    QHBoxLayout* fieldLayout = new QHBoxLayout();

    tableLayout->addWidget(table);
    tableLayout->addWidget(combobox);

    QLabel* id_label = new QLabel("Id");
    fieldLayout->addWidget(id_label);
    fieldLayout->addWidget(id_field);
    QLabel* denumire_label = new QLabel("Denumire");
    fieldLayout->addWidget(denumire_label);
    fieldLayout->addWidget(denumire_field);
    QLabel* tip_label = new QLabel("Tip");
    fieldLayout->addWidget(tip_label);
    fieldLayout->addWidget(tip_field);
    QLabel* numarRoti_label = new QLabel("Numar Roti");
    fieldLayout->addWidget(numarRoti_label);
    fieldLayout->addWidget(numarRoti_field);

    addLayout->addLayout(fieldLayout);
    addLayout->addWidget(addButton);

    mainLayout->addLayout(tableLayout);
    mainLayout->addLayout(addLayout);
    setLayout(mainLayout);
    show();
}

void Gui::init_signals() {
    QObject::connect(addButton, &QPushButton::clicked, [this]() {
        try {
            service.add_tractor(id_field->text().toStdString(), denumire_field->text().toStdString(), tip_field->text().toStdString(), numarRoti_field->text().toStdString());
            load_data();
        } catch (std::invalid_argument& e) {
            QMessageBox::information(this, "Eroare", e.what());
        }
    });

    QObject::connect(combobox, &QComboBox::currentTextChanged, [this](const QString& tip) {
       for (int i = 0; i < table->model()->rowCount(); i++) {
           if (table->model()->data(table->model()->index(i, 2)).toString() == tip) {
               for (int j = 0; j < table->model()->columnCount(); j++) {
                   table->model()->setData(table->model()->index(i, j), QBrush(Qt::red), Qt::BackgroundRole);
               }
           } else {
               for (int j = 0; j < table->model()->columnCount(); j++) {
                   table->model()->setData(table->model()->index(i, j), QBrush(Qt::transparent), Qt::BackgroundRole);
               }
           }
       }
    });
}