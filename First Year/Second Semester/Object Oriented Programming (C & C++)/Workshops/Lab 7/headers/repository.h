#pragma once
#include "vectordinamic.h"
#include "domain.h"

class Repository {
public:
    /*
     *  Constructor implicit
     */
    Repository();

    /*
     *  Returneaza lista de discipline
     */
    VectorDinamic<Disciplina>& get_lista_discipline();

    /*
     *  Adauga in lista de discipline o disciplina
     *  disciplina : disciplina pe care o adaugam in lista
     */
    void add_disciplina(const Disciplina& disciplina);

    /*
     *  Verifica daca exista disciplina
     */
    bool exista_disciplina(int id);

    /*
     *  Returneaza din lista de discipline o disciplina
     *  id : id-ul corespunzator disciplinei pe care o returnam
     */
    Disciplina& get_disciplina(int id);

    /*
     *  Sterge o disciplina din lista de discipline
     *  id : id-ul disciplinei pe care o stergem
     */
    void remove_disciplina(int id);

    /*
     *  Modifica o disciplina din lista de discipline
     *  id : id-ul disciplinei pe care o modificam
     */
    void update_disciplina(int id, const Disciplina& disciplina);

private:
    VectorDinamic<Disciplina> lista_discipline;
};
