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
    /**
     * Constructor implicit
     */
    RepositoryMemory();

    /**
     * Returneaza lista de discipline.
     * @return Referinta la vectorul de discipline.
     */
    std::vector<Disciplina>& get_lista_discipline() override;

    /**
     * Adauga in lista o disciplina.
     * @param disciplina Disciplina care se adauga.
     */
    void add_disciplina(const Disciplina& disciplina) override;

    /**
     * Verifica daca exista disciplina cu id-ul dat.
     * @param id ID-ul disciplinei cautate.
     * @return true daca exista, altfel false.
     */
    bool exista_disciplina(int id) const override;

    /**
     * Returneaza disciplina cu id-ul dat.
     * @param id ID-ul disciplinei cautate.
     * @return Referinta la disciplina gasita.
     */
    Disciplina& get_disciplina(int id) override;

    /**
     * Sterge disciplina cu id-ul dat.
     * @param id ID-ul disciplinei de sters.
     */
    void remove_disciplina(int id) override;

    /**
     * Actualizeaza disciplina cu id-ul dat.
     * @param id ID-ul disciplinei de actualizat.
     * @param disciplina Noua valoare pentru disciplina.
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
    /**
     * Constructor care initializeaza repository-ul si incarca datele din fisier.
     * @param filename Numele fisierului.
     */
    RepositoryFile(std::string filename) : RepositoryMemory(), filename(std::move(filename)) {
        loadFromFile();
    }

    /**
     * Adauga disciplina in fisier.
     * @param disciplina Disciplina care se adauga.
     */
    void add_disciplina(const Disciplina& disciplina) override;

    /**
     * Sterge disciplina din fisier.
     * @param id ID-ul disciplinei de sters.
     */
    void remove_disciplina(int id) override;
};

class RepositoryProbability : public RepositoryMemory {
public:
    /**
     * Constructor care initializeaza repository-ul si apeleaza generarea probabilistica.
     */
    RepositoryProbability()  {
        generate_probability();
    };

    /**
     * Genereaza un set de date cu probabilitate predefinita.
     */
    static void generate_probability();
};