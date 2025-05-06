#include "../headers/service.h"
#include "../headers/exceptions.h"
#include "../headers/undo.h"
#include <iostream>
#include <map>

std::string Service::add_disciplina(int id, const std::string& denumire, int ore, const std::string& tip, const std::string& cadru_didactic) {
    if (Validator::id_valid(id) == false) {
        throw NotValid("ID invalid!");
    }
    if (Validator::denumire_valida(denumire) == false) {
        throw NotValid("Denumire invalida!");
    }
    if (Validator::ore_valide(ore) == false) {
        throw NotValid("Numar de ore invalide!");
    }
    if (Validator::tip_valid(tip) == false) {
        throw NotValid("Tip invalid!");
    }
    if (repository->exista_disciplina(id) == true) {
        throw AlreadyExisting("Exista deja o disciplina cu acest ID!");
    }
    const Disciplina& disciplina = Disciplina(id, denumire, ore, tip, cadru_didactic);
    repository->add_disciplina(disciplina);
    lista_discipline_undo.push_back(std::make_unique<UndoAdauga>(*repository, disciplina));
    return "Operatie efectuata cu succes!";
}

std::string Service::remove_disciplina(int id) {
    if (!repository->exista_disciplina(id)) {
        throw NotExisting("Disciplina nu exista!");
    }
    const Disciplina& disciplina = repository->get_disciplina(id);
    lista_discipline_undo.push_back(std::make_unique<UndoSterge>(*repository, disciplina));
    repository->remove_disciplina(id);
    return "Operatie efectuata cu succes!";
}

std::string Service::update_disciplina(int id , const std::string &new_denumire, int new_ore, const std::string &new_tip, const std::string &new_cadru_didactic) {
    if (!repository->exista_disciplina(id)) {
        throw NotExisting("Disciplina nu exista!");
    }
    if (Validator::denumire_valida(new_denumire) == false) {
        throw NotValid("Denumire invalida!");
    }
    if (Validator::ore_valide(new_ore) == false) {
        throw NotValid("Numar de ore invalide!");
    }
    if (Validator::tip_valid(new_tip) == false) {
        throw NotValid("Tip invalid!");
    }
    const Disciplina& disciplina_veche = repository->get_disciplina(id);
    Disciplina disciplina = Disciplina(id, new_denumire, new_ore, new_tip, new_cadru_didactic);
    lista_discipline_undo.push_back(std::make_unique<UndoModifica>(*repository, disciplina_veche));
    repository->update_disciplina(id, disciplina);
    return "Operatie efectuata cu succes!";
}

Disciplina& Service::find_disciplina(int id) {
    if (!repository->exista_disciplina(id)) {
        throw NotExisting("Disciplina nu exista!");
    }
    Disciplina& disciplina = repository->get_disciplina(id);
    return disciplina;
}

std::vector<Disciplina>& Service::get_lista_discipline(){
    return repository->get_lista_discipline();
}

std::vector<Disciplina> Service::filtrare_discipline(std::vector<Disciplina>& lista_discipline, const std::string& camp_filtrare, const std::string& criteriu) {
    std::vector<Disciplina> lista_discipline_filtrata;
    if (camp_filtrare == "numar ore") {
        int numar_ore = stoi(criteriu);
        std::copy_if(lista_discipline.begin(), lista_discipline.end(),
            std::back_inserter(lista_discipline_filtrata),
            [numar_ore](Disciplina& disciplina) {
                return disciplina.get_ore() >= numar_ore;
            });

    }
    if (camp_filtrare == "cadru didactic") {
        const std::string& cadru_didactic = criteriu;
        std::copy_if(lista_discipline.begin(),lista_discipline.end(),
            std::back_inserter(lista_discipline_filtrata),
            [cadru_didactic](Disciplina& disciplina) {
                return disciplina.get_cadru_didactic() == cadru_didactic;
            });
    }
    return lista_discipline_filtrata;
}

void Service::sortare_discipline(std::vector<Disciplina>& lista_discipline, const std::string& criteriu) {
    if (criteriu == "denumire") {
        std::sort(lista_discipline.begin(), lista_discipline.end(),
          [](const Disciplina& a, const Disciplina& b) {
              return a.get_denumire() < b.get_denumire();
          });
    }if (criteriu == "numar ore") {
        std::sort(lista_discipline.begin(), lista_discipline.end(),
            [](const Disciplina& a, const Disciplina& b) {
                return a.get_ore() < b.get_ore();
            });
    }if (criteriu == "cadru didactic") {
        std::sort(lista_discipline.begin(), lista_discipline.end(),
            [](const Disciplina& a, const Disciplina& b) {
                return a.get_cadru_didactic() < b.get_cadru_didactic();
            });
    }if (criteriu == "tip") {
        std::sort(lista_discipline.begin(), lista_discipline.end(),
            [](const Disciplina& a, const Disciplina& b) {
                return a.get_tip() < b.get_tip();
            });
    }
}

std::map<std::string, DTO> Service::raport_discipline(std::vector<Disciplina>& lista_discipline) {
    std::map<std::string, DTO> frecventa_tip;

    for (Disciplina& disciplina : lista_discipline) {
        std::string tip = disciplina.get_tip();
        if (frecventa_tip.find(tip) == frecventa_tip.end()) {
            frecventa_tip[tip] = DTO(tip, 1);
        } else {
            frecventa_tip[tip].increment_aparitii();
        }
    }

    return frecventa_tip;
}

void Service::undo() {
    if (lista_discipline_undo.empty()) {
        throw std::runtime_error("Nu mai exista operatii de undo!");
    }
    lista_discipline_undo.back()->doUndo();
    lista_discipline_undo.pop_back();
}