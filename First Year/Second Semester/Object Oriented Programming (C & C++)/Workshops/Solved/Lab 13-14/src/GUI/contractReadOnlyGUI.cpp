#include "../headers/GUI/contractReadOnlyGUI.h"
#include <qwidget.h>
#include <qpainter.h>
#include <GUI/GUI.h>
#include <random>

void ContractReadOnlyGUI::paintEvent(QPaintEvent* event) {
    QPainter p{this};
    int x = 10;
    int y = 10;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> shape_dist(0, 2);

    for (const auto& d : contract.get_lista_discipline_contract()) {
        int shape = shape_dist(gen);
        if (shape == 0) {
            // cub
            p.drawRect(x, y, 30, 30);
        } else if (shape == 1) {
            // triunghi
            QPointF points[3] = {
                QPointF(x, y + 30),
                QPointF(x + 15, y),
                QPointF(x + 30, y + 30)
            };
            p.drawPolygon(points, 3);
        } else {
            // cerc
            p.drawEllipse(x, y, 30, 30);
        }
        x += 40;
        if (x > width() - 40) {
            x = 10;
            y += 50;
        }
    }
}

void ContractReadOnlyGUI::update() {
    repaint();
}

void ContractReadOnlyGUI::init_GUI() {
    resize(400, 300);
    setWindowTitle("Contract Read Only");
    show();
}