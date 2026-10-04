#include "../headers/validator.h"
#include "../headers/domain.h"
#include <vector>

bool Validator::id_valid(const std::string& id, std::vector<Apartament>& lista_apartamente) {
    for (const auto c : id) {
        if (c == ' ') {
            return false;
        }
    }
    try {
        std::stoi(id);
    } catch (...) {
        return false;
    }
    for (const auto& ap : lista_apartamente) {
        int int_id = std::stoi(id);
        if (ap.get_id() == int_id) {
            return false;
        }
    }
    return true;
}

bool Validator::suprafata_valida(const std::string& suprafata) {
    for (const auto c : suprafata) {
        if (c == ' ') {
            return false;
        }
    }
    if (suprafata.empty()) {
        return false;
    }
    if (suprafata.size() < 4) {
        return false;
    }
    if (suprafata.substr(suprafata.size() - 3) != "m^2") {
        return false;
    }
    try {
        std::stoi(suprafata.substr(0, suprafata.size() - 3));
    } catch (...) {
        return false;
    }
    return true;
}

bool Validator::strada_valida(const std::string& strada) {
    for (const auto c : strada) {
        if (c == ' ') {
            return false;
        }
    }
    if (strada.empty()) {
        return false;
    }
    return true;
}

bool Validator::pret_valid(const std::string& pret) {
    for (const auto c : pret) {
        if (c == ' ') {
            return false;
        }
    }
    try {
        std::stoi(pret);
    } catch (...) {
        return false;
    }
    return true;
}