#include <utility>

#include "../headers/service.h"

#include <cassert>
#include <iostream>
#include <set>

void Service::add_produs(const std::string& id, std::string nume, std::string tip, const std::string& pret) {
    try {
        stoi(id);
    } catch (...) {
        throw std::invalid_argument("ID must be a number!");
    }

    try {
        stod(pret);
    } catch (...) {
        throw std::invalid_argument("Pret must be a number!");
    }

    if (stod(pret) < 1 || stod(pret) > 100) {
        throw std::invalid_argument("Pret must be between 1 and 100!");
    }

    if (repository.exista_produs(stoi(id))) {
        throw std::invalid_argument("ID must be unique!");
    }

    repository.add_produs(Produs(stoi(id), std::move(nume), std::move(tip), stod(pret)));
}

void Service::load_from_file() {
    repository.load_from_file();
}

void Service::write_to_file() {
    repository.write_to_file();
}

bool Service::exista_tip(std::string tip) {
    return repository.exista_tip(tip);
}
