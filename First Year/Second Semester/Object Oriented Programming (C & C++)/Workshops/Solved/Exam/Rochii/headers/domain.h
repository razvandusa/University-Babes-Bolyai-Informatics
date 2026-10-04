#pragma once
#include <string>

class Rochie {
private:
    int cod;
    std::string denumire;
    std::string marime;
    int pret;
    std::string disponibilitate;

public:
    Rochie(int cod, std::string denumire, std::string marime, int pret, std::string disponibilitate) : cod(cod), denumire(denumire), marime(marime), pret(pret), disponibilitate(disponibilitate) {}

    int get_cod() {
        return cod;
    }

    std::string get_denumire() {
        return denumire;
    }

    std::string get_marime() {
        return marime;
    }

    int get_pret() {
        return pret;
    }

    std::string get_disponibilitate() {
        return disponibilitate;
    }

    void set_disponibilitate(std::string disponibilitate) {
        this->disponibilitate = std::move(disponibilitate);
    }

    bool operator== (Rochie other);

    ~Rochie() = default;

};
