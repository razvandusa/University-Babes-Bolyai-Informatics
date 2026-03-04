#include "../headers/domain.h"
bool Rochie::operator==(Rochie other) {
    if (this->get_pret() != other.get_pret()) {
        return false;
    }
    if (this->get_denumire() != other.get_denumire()) {
        return false;
    }
    if (this->get_disponibilitate() != other.get_disponibilitate()) {
        return false;
    }
    if (this->get_marime() != other.get_marime()) {
        return false;
    }
    return true;
}
