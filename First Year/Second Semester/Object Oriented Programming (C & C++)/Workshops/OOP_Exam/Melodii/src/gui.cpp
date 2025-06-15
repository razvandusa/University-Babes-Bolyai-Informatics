#include "../headers/gui.h"
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>

void Gui::load_data() {
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(5);
    model->setHorizontalHeaderLabels({"ID", "Titlu", "Artist", "Rank"});

    auto lista_melodii = service.get_melodii();
    sort(lista_melodii.begin(), lista_melodii.end(), [](const Melodie& m1, const Melodie& m2) {
    return m1.get_titlu() < m2.get_titlu();});
    service.write_to_file();

    int row = 0;
    for (const auto& produs : lista_melodii) {
        model->setItem(row, 0, new QStandardItem(QString::fromStdString(std::to_string(produs.get_id()))));
        model->setItem(row, 1 , new QStandardItem(QString::fromStdString(produs.get_titlu())));
        model->setItem(row, 2, new QStandardItem(QString::fromStdString(produs.get_artist())));
        model->setItem(row, 3, new QStandardItem(QString::fromStdString(std::to_string(produs.get_rank()))));
        model->setItem(row, 4, new QStandardItem(QString::fromStdString(std::to_string(service.count_rank(produs.get_rank())))));
        row++;
    }

    notify_observers();
    table->setModel(model);
}

void Gui::init_gui() {
    QHBoxLayout* layoutMain = new QHBoxLayout();

    QHBoxLayout* layoutTable = new QHBoxLayout();
    layoutTable->addWidget(table);

    QVBoxLayout* layoutUpdate = new QVBoxLayout();
    QHBoxLayout* layoutModifyTitle = new QHBoxLayout();
    QHBoxLayout* layoutModifyRank = new QHBoxLayout();
    QHBoxLayout* layoutButton = new QHBoxLayout();
    QLabel* labelMelodie = new QLabel("Titlu melodie");
    QLabel* labelRank = new QLabel("Rank melodie");

    layoutModifyTitle->addWidget(labelMelodie);
    layoutModifyTitle->addWidget(melodieTitle);
    layoutUpdate->addLayout(layoutModifyTitle);

    layoutModifyRank->addWidget(labelRank);
    melodieRank->setRange(1, 10);

    layoutModifyRank->addWidget(melodieRank);

    layoutUpdate->addLayout(layoutModifyRank);
    layoutButton->addWidget(buttonUpdate);
    layoutButton->addWidget(buttonDelete);

    layoutMain->addLayout(layoutTable);
    layoutMain->addLayout(layoutButton);
    layoutMain->addLayout(layoutUpdate);

    setLayout(layoutMain);

    Paint* paint = new Paint(service);
    add_observer(paint);
    paint->show();
}

void Gui::init_signal() {
    QObject::connect(table, &QTableView::clicked, [this](const QModelIndex& index) {
        id_selected = table->model()->index(index.row(), 0).data().toInt();
        auto lista_melodii = service.get_melodii();
        auto it = find_if(lista_melodii.begin(), lista_melodii.end(), [&](const Melodie& m) {
            return m.get_id() == id_selected;
        });
        melodieTitle->setText(QString::fromStdString(it->get_titlu()));
        melodieRank->setValue(it->get_rank());
    });

    QObject::connect(buttonUpdate, &QPushButton::clicked, [this]() {
        std::string titlu = melodieTitle->text().toStdString();
        int rank = melodieRank->value();
        service.update_melodie(id_selected, titlu, rank);
        load_data();
    });

    QObject::connect(buttonDelete, &QPushButton::clicked, [this]() {
        try {
            service.delete_melodie(id_selected);
        } catch (const std::invalid_argument& e) {
            QMessageBox::information(this, "Eroare", e.what());
        }
        load_data();
    });
}

void Paint::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    for (int i = 1; i <= 10; i++) {
        painter.drawLine(i * 10, 0, i * 10, service.count_rank(i) * 10);
    }
}
