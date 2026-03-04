#include "../headers/service.h"

#include <iostream>
#include <ostream>
Disciplina disciplina_vida = Disciplina();
/*
 *  Adauga o disciplina cu datele corespunzatoare daca sunt valide
 *  id - id-ul disciplinei pe care o adaugam
 *  ore - orele disciplinei pe care o adaugam
 *  tip - tipul disciplinei pe care o adaugam
 *  cadru_didactic - cadrul didactic al disciplinei pe care o adaugam
 */
std::string Service::add_disciplina(int id, std::string denumire, int ore, std::string tip, std::string cadru_didactic) {
    if (validator.id_valid(id) == false) {
        return "ID invalid!";
    }
    if (validator.denumire_valida(denumire) == false) {
        return "Denumire invalida!";
    }
    if (validator.ore_valide(ore) == false) {
        return "Numar de ore invalide!";
    }
    if (validator.tip_valid(tip) == false) {
        return "Tip invalid!";
    }
    if (repository.exista_disciplina(id) == true) {
        return "Exista deja o disciplina cu acest ID!";
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
        return "Disciplina nu exista!";
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
        return "Disciplina nu exista!";
    }
    if (validator.denumire_valida(new_denumire) == false) {
        return "Denumire invalida!";
    }
    if (validator.ore_valide(new_ore) == false) {
        return "Numar de ore invalide!";
    }
    if (validator.tip_valid(new_tip) == false) {
        return "Tip invalid!";
    }
    Disciplina disciplina = Disciplina(id, new_denumire, new_ore, new_tip, new_cadru_didactic);
    repository.update_disciplina(id, disciplina);
    return "Operatie efectuata cu succes!";
}

Disciplina& Service::find_disciplina(int id) {
    if (!repository.exista_disciplina(id)) {
        return disciplina_vida;
    }
    Disciplina& disciplina = repository.get_disciplina(id);
    return disciplina;
}

std::vector<Disciplina>& Service::get_lista_discipline(){
    return repository.get_lista_discipline();
}

std::vector<Disciplina> Service::filtrare_discipline(const std::vector<Disciplina>& lista_discipline, const std::string camp_filtrare, const std::string& criteriu) {
    std::vector<Disciplina> lista_discipline_filtrata;
    if (camp_filtrare == "numar ore") {
        int numar_ore = stoi(criteriu);
        for (const auto& disciplina : lista_discipline) {
            if (disciplina.get_ore() >= numar_ore) {
                lista_discipline_filtrata.push_back(disciplina);
            }
        }
    }
    if (camp_filtrare == "cadru didactic") {
        std::string cadru_didactic = criteriu;
        for (const auto& disciplina : lista_discipline) {
            if (disciplina.get_cadru_didactic() == cadru_didactic) {
                lista_discipline_filtrata.push_back(disciplina);
            }
        }
    }
    return lista_discipline_filtrata;
}

void Service::sortare_discipline(std::vector<Disciplina>& lista_discipline, const std::string& criteriu) {
    if (criteriu == "denumire") {
        bool sortat = false;
        while (!sortat) {
            sortat = true;
            for (auto disciplina = lista_discipline.begin(); disciplina < lista_discipline.end() - 1; ++disciplina) {
                auto next_disciplina = disciplina + 1;
                if (disciplina->get_denumire() > next_disciplina->get_denumire()) {
                    std::swap(*disciplina, *next_disciplina);
                    sortat = false;
                }
            }
        }
    }if (criteriu == "numar ore") {
        bool sortat = false;
        while (!sortat) {
            sortat = true;
            for (auto disciplina = lista_discipline.begin(); disciplina < lista_discipline.end() - 1; ++disciplina) {
                auto next_disciplina = disciplina + 1;
                if (disciplina->get_ore() > next_disciplina->get_ore()) {
                    std::swap(*disciplina, *next_disciplina);
                    sortat = false;
                }
            }
        }
    }if (criteriu == "cadru didactic") {
        bool sortat = false;
        while (!sortat) {
            sortat = true;
            for (auto disciplina = lista_discipline.begin(); disciplina < lista_discipline.end() - 1; ++disciplina) {
                auto next_disciplina = disciplina + 1;
                if (disciplina->get_cadru_didactic() > next_disciplina->get_cadru_didactic()) {
                    std::swap(*disciplina, *next_disciplina);
                    sortat = false;
                }
            }
        }
    }if (criteriu == "tip") {
        bool sortat = false;
        while (!sortat) {
            sortat = true;
            for (auto disciplina = lista_discipline.begin(); disciplina < lista_discipline.end() - 1; ++disciplina) {
                auto next_disciplina = disciplina + 1;
                if (disciplina->get_tip() > next_disciplina->get_tip()) {
                    std::swap(*disciplina, *next_disciplina);
                    sortat = false;
                }
            }
        }
    }
}