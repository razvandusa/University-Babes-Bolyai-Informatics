#pragma once
#include <map>
#include <memory>
#include "repository.h"
#include "exceptions.h"
#include "undo.h"
#include "validator.h"

class DTO {
private:
    std::string tip;
    int aparitii;
public:
    DTO() : tip(""), aparitii(0) {}

    DTO (const std::string& tip, int aparitii) : tip(tip), aparitii(aparitii) {}

    const std::string& get_denumire() const {
        return tip;
    }

    int get_aparitii() const {
        return aparitii;
    }

    void increment_aparitii() {
        aparitii++;
    }

};

class Service {
public:
    /*
     *  Constructorul clasei Service
     */
    Service(std::unique_ptr<RepositoryMemory> repo) : repository(std::move(repo)) {
        lista_discipline_undo.reserve(100);
    }

    /*
     *  Adauga o disciplina in lista de discipline cu datele corespunzatoare
     *  id - id-ul disciplinei pe care o adaugam
     *  ore - orele disciplinei pe care o adaugam
     *  tip - tipul disciplinei pe care o adaugam
     *  cadru_didactic - cadrul didactic al disciplinei pe care o adaugam
     */
    std::string add_disciplina(int id, const std::string& denumire, int ore, const std::string& tip, const std::string& cadru_didactic);

    /*
     *  Sterge disciplina din lista de discipline
     *  id - id-ul disciplinei pe care o stergem
     */
    std::string remove_disciplina(int id);

    /*
     *  Modifica datele unei discipline din lista de discipline
     *  id - id-ul disciplinei pe care o modificam
     *  new_ore - orele noi a disciplinei pe care o modificam
     *  tip - tipul nou a disciplinei pe care o modificam
     *  cadru_didactic - cadrul didactic nou al disciplinei pe care o modificam
     */
    std::string update_disciplina(int id , const std::string &new_denumire, int new_ore, const std::string &new_tip, const std::string &new_cadru_didactic);

    /*
    *  Cautam o disciplina dupa un id si o returnam
    *  id - id-ul disciplinei pe care o cautam
    */
    Disciplina& find_disciplina(int id);

    /*
     *  Returneaza lista de discipline
     */
    std::vector<Disciplina>& get_lista_discipline();

    /*
     *  Filtreaza ofertele dupa criteriul care poate sa fie destinatie sau pret
     *  lista_discipline - lista de discipline pe care o filtram
     *  camp_filtrare - campul dupa care filtram
     *  criteriu - criteriul dupa care filtram
     */
    static std::vector<Disciplina> filtrare_discipline(std::vector<Disciplina>& lista_discipline, const std::string& camp_filtrare, const std::string& criteriu);

    /*
     *  Sorteaza ofertele dupa criteriul care poate sa fie denumire, destinatie, tip sau pret
     *  lista_discipline - lista de discipline pe care o sortam
     *  criteriu - criteriul dupa care sortam
     */
    static void sortare_discipline(std::vector<Disciplina>& lista_discipline, const std::string& criteriu);

    /*
     *  Afiseaza un raport cu frecventa fiecarui tip din lista
     *  lista_discipline - llista de discipline unde cautam frecventa tipurilor
     */
    static std::map<std::string, DTO> raport_discipline(std::vector<Disciplina>& lista_discipline);

    /*
     *  Realizeaza operatia de undo
     */
    void undo();
private:
    std::unique_ptr<RepositoryMemory> repository;
    Validator validator;
    std::vector<std::unique_ptr<ActiuneUndo>> lista_discipline_undo;
};
