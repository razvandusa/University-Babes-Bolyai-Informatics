#include "../headers/service.h"
#include <iostream>
/*
 *  Adauga o disciplina cu datele corespunzatoare daca sunt valide
 *  id - id-ul disciplinei pe care o adaugam
 *  ore - orele disciplinei pe care o adaugam
 *  tip - tipul disciplinei pe care o adaugam
 *  cadru_didactic - cadrul didactic al disciplinei pe care o adaugam
 */
std::string Service::add_disciplina(int id, const std::string& denumire, int ore, const std::string& tip, const std::string& cadru_didactic) {
    if (Validator::id_valid(id) == false) {
        throw std::invalid_argument("ID invalid!");
    }
    if (Validator::denumire_valida(denumire) == false) {
        throw std::invalid_argument("Denumire invalida!");
    }
    if (Validator::ore_valide(ore) == false) {
        throw std::invalid_argument("Numar de ore invalide!");
    }
    if (Validator::tip_valid(tip) == false) {
        throw std::invalid_argument("Tip invalid!");
    }
    if (repository.exista_disciplina(id) == true) {
        throw std::invalid_argument("Exista deja o disciplina cu acest ID!");
    }
    Disciplina disciplina = Disciplina(id, denumire, ore, tip, cadru_didactic);
    repository.add_disciplina(disciplina);
    return "Operatie efectuata cu succes!";
}

/*
 *  Sterge o disciplina cu id-ul corespunzator daca este valid
 *  id - id-ul disciplinei pe care o stergem
 */
std::string Service::remove_disciplina(int id) {
    if (!repository.exista_disciplina(id)) {
        throw std::invalid_argument("Disciplina nu exista!");
    }
    repository.remove_disciplina(id);
    return "Operatie efectuata cu succes!";
}

/*
 *  Facem update datelor unei discipline daca aceasta exista
 *  id - id-ul disciplinei pe care o updatam
 *  new_denumire - denumirea noua a disciplinei
 *  new_ore - ora noua a disciplinei
 *  new_tip - tipul nou al disciplinei
 *  new_cadru_didactic - cadrul didactic nou al disciplinei
 */
std::string Service::update_disciplina(int id , const std::string &new_denumire, int new_ore, const std::string &new_tip, const std::string &new_cadru_didactic) {
    if (!repository.exista_disciplina(id)) {
        throw std::invalid_argument("Disciplina nu exista!");
    }
    if (Validator::denumire_valida(new_denumire) == false) {
        throw std::invalid_argument("Denumire invalida!");
    }
    if (Validator::ore_valide(new_ore) == false) {
        throw std::invalid_argument("Numar de ore invalide!");
    }
    if (Validator::tip_valid(new_tip) == false) {
        throw std::invalid_argument("Tip invalid!");
    }
    Disciplina disciplina = Disciplina(id, new_denumire, new_ore, new_tip, new_cadru_didactic);
    repository.update_disciplina(id, disciplina);
    return "Operatie efectuata cu succes!";
}

Disciplina& Service::find_disciplina(int id) {
    if (!repository.exista_disciplina(id)) {
        throw std::invalid_argument("Disciplina nu exista!");
    }
    Disciplina& disciplina = repository.get_disciplina(id);
    return disciplina;
}

VectorDinamic<Disciplina>& Service::get_lista_discipline(){
    return repository.get_lista_discipline();
}

VectorDinamic<Disciplina> Service::filtrare_discipline(VectorDinamic<Disciplina>& lista_discipline, const std::string camp_filtrare, const std::string& criteriu) {
    VectorDinamic<Disciplina> lista_discipline_filtrata;
    if (camp_filtrare == "numar ore") {
        int numar_ore = stoi(criteriu);
        for (auto iterator = lista_discipline.begin(); iterator != lista_discipline.end(); ++iterator) {
            if (iterator.element().get_ore() >= numar_ore) {
                lista_discipline_filtrata.adaugare(iterator.element());
            }
        }
    }
    if (camp_filtrare == "cadru didactic") {
        const std::string& cadru_didactic = criteriu;
        for (auto iterator = lista_discipline.begin(); iterator != lista_discipline.end(); ++iterator) {
            if (iterator.element().get_cadru_didactic() == cadru_didactic) {
                lista_discipline_filtrata.adaugare(iterator.element());
            }
        }
    }
    return lista_discipline_filtrata;
}

void Service::sortare_discipline(VectorDinamic<Disciplina>& lista_discipline, const std::string& criteriu) {
    if (criteriu == "denumire") {
        bool sortat = false;
        while (!sortat) {
            sortat = true;
            for (auto iterator = lista_discipline.begin(); iterator != lista_discipline.end() - 1; ++iterator) {
                auto next_iterator = iterator + 1;
                if (iterator.element().get_denumire() > next_iterator.element().get_denumire()) {
                    std::swap(*iterator, *next_iterator);
                    sortat = false;
                }
            }
        }
    }if (criteriu == "numar ore") {
        bool sortat = false;
        while (!sortat) {
            sortat = true;
            for (auto iterator = lista_discipline.begin(); iterator != lista_discipline.end() - 1; ++iterator) {
                auto next_iterator = iterator + 1;
                if (iterator.element().get_ore() > next_iterator.element().get_ore()) {
                    std::swap(*iterator, *next_iterator);
                    sortat = false;
                }
            }
        }
    }if (criteriu == "cadru didactic") {
        bool sortat = false;
        while (!sortat) {
            sortat = true;
            for (auto iterator = lista_discipline.begin(); iterator != lista_discipline.end() - 1; ++iterator) {
                auto next_iterator = iterator + 1;
                if (iterator.element().get_cadru_didactic() > next_iterator.element().get_cadru_didactic()) {
                    std::swap(*iterator, *next_iterator);
                    sortat = false;
                }
            }
        }
    }if (criteriu == "tip") {
        bool sortat = false;
        while (!sortat) {
            sortat = true;
            for (auto iterator = lista_discipline.begin(); iterator != lista_discipline.end() - 1; ++iterator) {
                auto next_iterator = iterator + 1;
                if (iterator.element().get_tip() > next_iterator.element().get_tip()) {
                    std::swap(*iterator, *next_iterator);
                    sortat = false;
                }
            }
        }
    }
}