#pragma once
#include <string>

class Produs {
public:
    Produs(int id, std::string nume, std::string tip, double pret) : id(id), nume(nume), tip(tip), pret(pret) {};

    /**
     * Returneaza id-ul produsului
     * @return int id
     */
    int get_id() {
        return id;
    }

    /**
     * Returneaza numele produsului
     * @return std::string nume
     */
    std::string get_nume() {
        return nume;
    }

    /**
     * Returneaza tipul produsului
     * @return std::string tip
     */
    std::string get_tip() {
        return tip;
    }

    /**
     * Returneaza pretul produsului
     * @return double pret
     */
    double get_pret() {
        return pret;
    }

private:
    int id;
    std::string nume;
    std::string tip;
    double pret;
};