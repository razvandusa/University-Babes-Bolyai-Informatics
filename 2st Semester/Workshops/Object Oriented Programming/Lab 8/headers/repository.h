#pragma once

#include "vector"
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
    std::vector<Disciplina>& get_lista_discipline();

    /*
     *  Adauga in lista de discipline o disciplina
     *  disciplina : disciplina pe care o adaugam in lista
     */
    virtual void add_disciplina(const Disciplina& disciplina);

    /*
     *  Verifica daca exista disciplina
     */
    bool exista_disciplina(int id) const;

    /*
     *  Returneaza din lista de discipline o disciplina
     *  id : id-ul corespunzator disciplinei pe care o returnam
     */
    Disciplina& get_disciplina(int id);

    /*
     *  Sterge o disciplina din lista de discipline
     *  id : id-ul disciplinei pe care o stergem
     */
    virtual void remove_disciplina(int id);

    /*
     *  Modifica o disciplina din lista de discipline
     *  id : id-ul disciplinei pe care o modificam
     */
    void update_disciplina(int id, const Disciplina& disciplina);

    /*
     *  Destructor
     */
    virtual ~Repository() = default;

private:
    std::vector<Disciplina> lista_discipline;
};

class RepositoryFile : public Repository {
private:
    std::string filename;
    void loadFromFile();
    void writeToFile();
public:
    /*
     *  Constructor
     */
    RepositoryFile(std::string filename) : Repository(), filename(std::move(filename)) {
        loadFromFile();
    }

    /*
     *  Adauga in fisier o disciplina
     *  disciplina : disciplina pe care o adaugam in lista
     */
    void add_disciplina(const Disciplina& disciplina) override;

    /*
     *  Sterge o disciplina din fisier
     *  id : id-ul disciplinei pe care o stergem
     */
    void remove_disciplina(int id) override;
};
