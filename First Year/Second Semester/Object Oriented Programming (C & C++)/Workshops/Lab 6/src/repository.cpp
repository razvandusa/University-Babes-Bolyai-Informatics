#include "../headers/repository.h"
/*
 *  Constructor implicit
 */
Repository::Repository() {
    lista_discipline = std::vector<Disciplina> {};
}

/*
 *  Returneaza lista de discipline
 */
std::vector<Disciplina>& Repository::get_lista_discipline() {
    return lista_discipline;
}

/*
 *  Adauga in lista de discipline o disciplina
 */
void Repository::add_disciplina(const Disciplina& disciplina) {
    lista_discipline.push_back(disciplina);
}

/*
 *  Verifica daca exista disciplina
 */
bool Repository::exista_disciplina(int id) {
    for (const auto &disciplina : lista_discipline) {
        if (disciplina.get_id() == id) {
            return true;
        }
    }
    return false;
}

/*
 *  Returneaza din lista de discipline o disciplina
 *  id : id-ul corespunzator disciplinei pe care o returnam
 */
Disciplina& Repository::get_disciplina(int id) {
    for (auto &disciplina : lista_discipline) {
        if (disciplina.get_id() == id) {
            return disciplina;
        }
    }
}

/*
 *  Sterge o disciplina din lista de discipline
 *  id : id-ul disciplinei pe care o stergem
 */
void Repository::remove_disciplina(int id) {
    for (auto disciplina = lista_discipline.begin(); disciplina < lista_discipline.end(); ++disciplina) {
        if (disciplina->get_id() == id) {
            lista_discipline.erase(disciplina);
        }
    }
}

/*
 *  Modifica o disciplina din lista de discipline
 *  id : id-ul disciplinei pe care o modificam
 */
void Repository::update_disciplina(int id, const Disciplina& updated_disciplina) {
    Disciplina& disciplina = get_disciplina(id);
    disciplina = updated_disciplina;
}
