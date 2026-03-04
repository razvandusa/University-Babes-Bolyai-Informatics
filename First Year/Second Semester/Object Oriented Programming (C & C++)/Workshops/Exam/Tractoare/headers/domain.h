#pragma once
#include <string>

class Tractor {
public:
    Tractor(int id, std::string denumire, std::string tip, int numarRoti) : id(id), denumire(move(denumire)), tip(move(tip)), numarRoti(numarRoti) {}

    int get_id() const { return id; }
    std::string get_denumire() const { return denumire; }
    std::string get_tip() const { return tip; }
    int get_numarRoti() const { return numarRoti; }

private:
    int id;
    std::string denumire;
    std::string tip;
    int numarRoti;
};
