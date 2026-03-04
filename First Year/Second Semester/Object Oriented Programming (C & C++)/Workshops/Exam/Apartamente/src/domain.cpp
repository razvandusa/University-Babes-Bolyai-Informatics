#include "../headers/domain.h"
Apartament::Apartament(const Apartament &other) {
    this->id = other.id;
    this->suprafata = other.suprafata;
    this->strada = other.strada;
    this->pret = other.pret;
}


bool Apartament::operator==(const Apartament &other) const {
    if (get_pret() != other.get_pret()) {
        return false;
    }
    if (get_strada() != other.get_strada()) {
        return false;
    }
    if (get_suprafata() != other.get_suprafata()) {
        return false;
    }
    return true;
}
