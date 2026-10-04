#pragma once
#include <vector>
#include <domain.h>
#include <QAbstractTableModel>

class TabelModel : public QAbstractTableModel {
private:
    std::vector<Disciplina> lista_discipline;
public:
    TabelModel(const std::vector<Disciplina>& lista_discipline, QObject* parent = nullptr)
        : QAbstractTableModel(parent), lista_discipline(lista_discipline) {
    }
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return lista_discipline.size();
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() < 0 || index.row() >= lista_discipline.size() || index.column() < 0 || index.column() >= 5)
            return QVariant();
        if (role == Qt::DisplayRole) {
            const Disciplina& d = lista_discipline[index.row()];
            switch (index.column()) {
                case 0:
                    return d.get_id();
                case 1:
                    return QString::fromStdString(d.get_denumire());
                case 2:
                    return d.get_ore();
                case 3:
                    return QString::fromStdString(d.get_tip());
                case 4:
                    return QString::fromStdString(d.get_cadru_didactic());
                default:
                    return QVariant();
            }
        }
        return QVariant();
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole)
            return QVariant();
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("ID");
                case 1:
                    return QString("Denumire");
                case 2:
                    return QString("Ore");
                case 3:
                    return QString("Tip");
                case 4:
                    return QString("Cadru Didactic");
                default:
                    return QVariant();
            }
        }
        return QVariant();
    }

    void updateDiscipline(const std::vector<Disciplina>& new_lista_discipline) {
        this->lista_discipline = new_lista_discipline;
        if (!lista_discipline.empty()) {
            emit dataChanged(createIndex(0, 0), createIndex(static_cast<int>(lista_discipline.size()) - 1, 4), { Qt::DisplayRole });
        } else {
            beginResetModel();
            endResetModel();
        }
    }
};