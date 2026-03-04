#include "../headers/contractCrud.h"
#include <QVBoxLayout>
#include <random>
#include <algorithm>
#include <QPainter>

ContractCrud::ContractCrud() {
    cos = std::vector<Disciplina> {};
    cos.reserve(100);
}

void ContractCrud::clear_contract() {
    cos.clear();
}

void ContractCrud::add_disciplina(int id, Service &service) {
    for (const auto & disciplina : cos) {
        if (disciplina.get_id() == id) {
            throw AlreadyExisting("Aceasta disciplina exista deja in contract!");
        }
    }
    const auto disciplina = service.find_disciplina(id);
    cos.emplace_back(disciplina);
}

void ContractCrud::generate_contract(int number_to_generate, Service &service) {
    if (service.get_lista_discipline().empty()) {
        throw NotExisting("Nu se poate genera contractul pentru ca lista de discipline este goala!");
    }

    if (number_to_generate > service.get_lista_discipline().size()) {
        throw NotValid("Nu exista suficiente discipline in lista pentru a genera contractul!");
    }

    this->clear_contract();

    const auto& lista_discipline = service.get_lista_discipline();
    auto total = service.get_lista_discipline().size();
    std::vector<int> random_num;
    random_num.reserve(total);
    for (int i = 0; i < total; i++) {
        random_num.push_back(lista_discipline[i].get_id());
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(random_num.begin(), random_num.end(), g);

    for (int i = 0; i < number_to_generate; i++) {
        add_disciplina(random_num[i],service);
    }
}

void ContractCrud::reload_contract(std::vector<Disciplina>& lista_discipline) {
    clear_contract();
    for (const auto& disciplina : lista_discipline) {
        cos.emplace_back(disciplina);
    }
}