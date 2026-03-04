#pragma once

#include "vector"
#include "domain.h"
class RepositoryAbstract {
public:
    virtual void add_disciplina(const Disciplina& disciplina) = 0;
    virtual void remove_disciplina(int id) = 0;
    virtual bool exista_disciplina(int id) const = 0;
    virtual void update_disciplina(int id, const Disciplina& disciplina) = 0;
    virtual Disciplina& get_disciplina(int id) = 0;
    virtual std::vector<Disciplina>& get_lista_discipline() = 0;
    virtual ~RepositoryAbstract() = default;
};

class RepositoryMemory : RepositoryAbstract {
public:
    /*
     *  Constructor implicit
     */
    RepositoryMemory();

    /*
     *  Returneaza lista de discipline
     */
    std::vector<Disciplina>& get_lista_discipline() override;

    /*
     *  Adauga in lista de discipline o disciplina
     *  disciplina : disciplina pe care o adaugam in lista
     */
    void add_disciplina(const Disciplina& disciplina) override;

    /*
     *  Verifica daca exista disciplina
     */
    bool exista_disciplina(int id) const override;

    /*
     *  Returneaza din lista de discipline o disciplina
     *  id : id-ul corespunzator disciplinei pe care o returnam
     */
    Disciplina& get_disciplina(int id) override;

    /*
     *  Sterge o disciplina din lista de discipline
     *  id : id-ul disciplinei pe care o stergem
     */
    void remove_disciplina(int id) override;

    /*
     *  Modifica o disciplina din lista de discipline
     *  id : id-ul disciplinei pe care o modificam
     */
    void update_disciplina(int id, const Disciplina& disciplina) override;

private:
    std::vector<Disciplina> lista_discipline;
};

class RepositoryFile : public RepositoryMemory {
private:
    std::string filename;
    void loadFromFile();
    void writeToFile();
public:
    /*
     *  Constructor
     */
    RepositoryFile(std::string filename) : RepositoryMemory(), filename(std::move(filename)) {
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

class RepositoryProbability : public RepositoryMemory {
public:
    /*
     *  Constructor
     */
    RepositoryProbability()  {
        generate_probability();
    };

    static void generate_probability();
};