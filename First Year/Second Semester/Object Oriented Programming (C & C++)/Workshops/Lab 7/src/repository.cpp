#include "../headers/repository.h"
Disciplina disciplina_vida;
/*
 *  Constructor implicit
 */
Repository::Repository() {
    lista_discipline = VectorDinamic<Disciplina> {};
}

/*
 *  Returneaza lista de discipline
 */
VectorDinamic<Disciplina>& Repository::get_lista_discipline() {
    return lista_discipline;
}

/*
 *  Adauga in lista de discipline o disciplina
 */
void Repository::add_disciplina(const Disciplina& disciplina) {
    lista_discipline.adaugare(disciplina);
}

/*
 *  Verifica daca exista disciplina
 */
bool Repository::exista_disciplina(int id) {
    for (auto iterator = lista_discipline.begin(); iterator != lista_discipline.end(); ++iterator) {
        if (iterator.element().get_id() == id) {
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
    for (auto iterator = lista_discipline.begin(); iterator != lista_discipline.end(); ++iterator) {
        if (iterator.element().get_id() == id) {
            return iterator.element();
        }
    }
    return disciplina_vida;
}

/*
 *  Sterge o disciplina din lista de discipline
 *  id : id-ul disciplinei pe care o stergem
 */
void Repository::remove_disciplina(int id) {
    for (auto iterator = lista_discipline.begin(); iterator != lista_discipline.end(); ++iterator) {
        if (iterator.element().get_id() == id) {
            lista_discipline.sterge(iterator.get_curent());
            break;
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
