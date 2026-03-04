#include "../headers/service.h"
void Service::add_tractor(const std::string& id, const std::string& denumire, const std::string &tip,const std::string& numarRoti) {
    try {
        stoi(id);
    } catch (...) {
        throw std::invalid_argument("Id-ul trebuie sa fie intreg!");
    }

    try {
        stoi(numarRoti);
    } catch (...) {
        throw std::invalid_argument("Numarul de roti trebuie sa fie intreg!");
    }

    if (id.empty() or denumire.empty() or tip.empty() or numarRoti.empty()) {
        throw std::invalid_argument("Textfield-ul trebuie sa nu fie vid!");
    }

    if (2 > stoi(numarRoti) or stoi(numarRoti) > 16) {
        throw std::invalid_argument("Numarul de roti trebuie sa fie cuprins intre 2 si 16!");
    }

    if (stoi(numarRoti) % 2 != 0) {
        throw std::invalid_argument("Numarul de roti trebuie sa fie par!");
    }

    if (exista_id(stoi(id))) {
        throw std::invalid_argument("Id-ul deja existent!");
    }

    repository.add_tractor(Tractor(stoi(id), denumire, tip, stoi(numarRoti)));
}
