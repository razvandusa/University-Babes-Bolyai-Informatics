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
    /**
     * Constructorul clasei Service.
     */
    Service(std::unique_ptr<RepositoryMemory> repo) : repository(std::move(repo)) {
        lista_discipline_undo.reserve(100);
    }

    /**
     * Adauga o disciplina in lista de discipline.
     * @param id ID-ul disciplinei.
     * @param denumire Denumirea disciplinei.
     * @param ore Numarul de ore.
     * @param tip Tipul disciplinei.
     * @param cadru_didactic Cadrul didactic.
     * @return Mesaj de confirmare.
     */
    std::string add_disciplina(int id, const std::string& denumire, int ore, const std::string& tip, const std::string& cadru_didactic);

    /**
     * Sterge disciplina cu ID-ul dat.
     * @param id ID-ul disciplinei de sters.
     * @return Mesaj de confirmare.
     */
    std::string remove_disciplina(int id);

    /**
     * Modifica o disciplina existenta.
     * @param id ID-ul disciplinei de modificat.
     * @param new_denumire Noua denumire.
     * @param new_ore Noul numar de ore.
     * @param new_tip Noul tip.
     * @param new_cadru_didactic Noul cadru didactic.
     * @return Mesaj de confirmare.
     */
    std::string update_disciplina(int id , const std::string &new_denumire, int new_ore, const std::string &new_tip, const std::string &new_cadru_didactic);

    /**
     * Cauta o disciplina dupa ID.
     * @param id ID-ul disciplinei.
     * @return Referinta la disciplina gasita.
     */
    Disciplina& find_disciplina(int id);

    /**
     * Returneaza lista tuturor disciplinelor.
     * @return Referinta la vectorul de discipline.
     */
    std::vector<Disciplina>& get_lista_discipline();

    /**
     * Filtreaza disciplinele dupa un anumit camp si criteriu.
     * @param lista_discipline Lista de discipline de filtrat.
     * @param camp_filtrare Campul dupa care se filtreaza.
     * @param criteriu Valoarea de filtrare.
     * @return Lista filtrata.
     */
    static std::vector<Disciplina> filtrare_discipline(std::vector<Disciplina>& lista_discipline, const std::string& camp_filtrare, const std::string& criteriu);

    /**
     * Sorteaza disciplinele dupa un criteriu.
     * @param lista_discipline Lista de discipline de sortat.
     * @param criteriu Criteriul de sortare.
     */
    static void sortare_discipline(std::vector<Disciplina>& lista_discipline, const std::string& criteriu);

    /**
     * Genereaza un raport al frecventei pentru fiecare tip de disciplina.
     * @param lista_discipline Lista de discipline.
     * @return Map cu tipul si frecventa aferenta (DTO).
     */
    static std::map<std::string, DTO> raport_discipline(std::vector<Disciplina>& lista_discipline);

    /**
     * Executa operatia de undo pentru ultima modificare.
     */
    void undo();
private:
    std::unique_ptr<RepositoryMemory> repository;
    Validator validator;
    std::vector<std::unique_ptr<ActiuneUndo>> lista_discipline_undo;
};
