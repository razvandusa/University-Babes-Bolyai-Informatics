#include "../headers/gui.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>

void Gui::load_data() {
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(5);
    model->setHorizontalHeaderLabels({"ID", "Nume", "Tip", "Pret", "Numar vocale"});

    auto lista_produse = service.get_all();

    sort(lista_produse.begin(), lista_produse.end(), [](Produs& p1, Produs& p2) {
        return p1.get_nume() < p2.get_nume();
    });

    std::set<std::string> set;
    for (auto produs : lista_produse) {
        if (!set.contains(produs.get_tip())) {
            auto* window = new WindowTip(produs.get_tip(), 1);
            service.add_observer(window);
            set.insert(produs.get_tip());
        } else {
            service.notify_observers(produs.get_tip());
        }

        QList<QStandardItem*> row;
        row.append(new QStandardItem(QString::fromStdString(std::to_string(produs.get_id()))));
        row.append(new QStandardItem(QString::fromStdString(produs.get_nume())));
        row.append(new QStandardItem(QString::fromStdString(produs.get_tip())));
        row.append(new QStandardItem(QString::fromStdString(std::to_string(produs.get_pret()))));
        int count = 0;
        for (auto c : produs.get_nume()) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                count++;
            }
        }
        row.append(new QStandardItem(QString::fromStdString(std::to_string(count))));

        model->appendRow(row);
    }

    table->setModel(model);
}

void Gui::init_gui() {

    QVBoxLayout *layoutButtons = new QVBoxLayout();
    layoutButtons->addWidget(new QLabel("ID"));
    layoutButtons->addWidget(id_field);
    layoutButtons->addWidget(new QLabel("Nume"));
    layoutButtons->addWidget(nume_field);
    layoutButtons->addWidget(new QLabel("Tip"));
    layoutButtons->addWidget(tip_field);
    layoutButtons->addWidget(new QLabel("Pret"));
    layoutButtons->addWidget(pret_field);
    layoutButtons->addWidget(buttonAdd);

    QVBoxLayout *layoutSlider = new QVBoxLayout();
    layoutSlider->addWidget(slider);
    layoutSlider->addWidget(sliderValue);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(table);
    mainLayout->addLayout(layoutButtons);
    mainLayout->addLayout(layoutSlider);
    setLayout(mainLayout);
    show();
}


void Gui::init_signals() {
    QObject::connect(buttonAdd, &QPushButton::clicked, [&]() {
        auto id = id_field->text().toStdString();
        auto nume = nume_field->text().toStdString();
        auto tip = tip_field->text().toStdString();
        auto pret = pret_field->text().toStdString();
        try {
            service.add_produs(id, nume, tip, pret);
            if (!service.exista_tip(tip)) {
                auto* window = new WindowTip(tip, 1);
                service.add_observer(window);
            } else {
                service.notify_observers(tip);
            }
            service.write_to_file();
        } catch (...) {
            QMessageBox::information(this, "Error", "Invalid input!");
        }
    });

    QObject::connect(slider, &QSlider::valueChanged, [&](int value) {
        sliderValue->setText(QString::fromStdString("Value : " + std::to_string(value)));

        auto model = table->model();
        if (!model) return;

        for (int row = 0; row < model->rowCount(); row++) {
            auto pret = model->index(row, 3).data().toString().toDouble();
            if (pret < value) {
                for (int col = 0; col < model->columnCount(); col++) {
                    auto index = model->index(row, col);
                    model->setData(index, QBrush(Qt::red), Qt::BackgroundRole);
                }
            } else {
                for (int col = 0; col < model->columnCount(); col++) {
                    auto index = model->index(row, col);
                    model->setData(index, QBrush(Qt::transparent), Qt::BackgroundRole);
                }
            }
        }
    });
}

void WindowTip::init_gui() {
    setWindowTitle(QString::fromStdString(tip));
    setFixedSize(200, 100);
    QHBoxLayout *layout = new QHBoxLayout();
    label->setText(QString::fromStdString(std::to_string(count)));
    layout->addWidget(label);
    setLayout(layout);
}

void WindowTip::update(std::string tip) {
    if (tip == this->tip) {
        count += 1;
        label->setText(QString::fromStdString(std::to_string(count)));
    }
}