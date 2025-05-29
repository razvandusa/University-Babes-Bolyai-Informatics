#include "../headers/contract.h"
#include "../headers/exceptions.h"
#include <random>
#include <fstream>

Contract::Contract() {
    contract = std::vector<Disciplina> {};
    contract.reserve(100);
}

std::vector<Disciplina>& Contract::get_lista_discipline_contract() {
    return contract;
}

void Contract::clear_contract() {
    get_lista_discipline_contract().clear();
}

void Contract::add_disciplina_contract(int id, Service &service) {
    for (const auto & disciplina : contract) {
        if (disciplina.get_id() == id) {
            throw AlreadyExisting("Aceasta disciplina exista deja in contract!");
        }
    }
    const auto disciplina = service.find_disciplina(id);
    contract.push_back(disciplina);
}

void Contract::generate_contract(int number_to_generate, Service &service) {
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
    std::ranges::shuffle(random_num, g);

    for (int i = 0; i < number_to_generate; i++) {
        add_disciplina_contract(random_num[i],service);
    }
}

void Contract::export_contract(std::string& file_name) const {
    if (file_name.size() < 4 ||
        (file_name.substr(file_name.size() - 4) != ".csv" &&
         file_name.substr(file_name.size() - 5) != ".html")) {
        throw NotValid("Fisierul trebuie sa aiba extensia .csv sau .html!");
    }
    file_name = "/Users/razvandusa/CLionProjects/Lab 13-14/" + file_name;
    std::ofstream fout(file_name);

    for (const auto &disciplina : contract) {
        fout << disciplina.get_id() << std::endl;
        fout << disciplina.get_denumire() << std::endl;
        fout << disciplina.get_ore() << std::endl;
        fout << disciplina.get_tip() << std::endl;
        fout << disciplina.get_cadru_didactic() << std::endl;
        fout << std::endl;
    }
}
