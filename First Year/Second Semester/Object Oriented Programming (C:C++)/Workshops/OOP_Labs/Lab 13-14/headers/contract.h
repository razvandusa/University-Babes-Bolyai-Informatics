#pragma once
#include "service.h"
#include "observer.h"

class Contract {
    private:
        std::vector<Disciplina> contract;

    public:
        /**
         * Constructor implicit
         */
        Contract();

        /**
         * Sterge toate disciplinele din contract.
         */
        void clear_contract();

        /**
         * Adauga o disciplina in contract.
         * @param id ID-ul disciplinei de adaugat.
         * @param service Containerul din care se vor lua disciplinele.
         */
        void add_disciplina_contract(int id, Service &service);

        /**
         * Genereaza un contract.
         * @param number_to_generate Numarul de discipline care trebuie generate.
         * @param service Containerul din care se vor lua disciplinele.
         */
        void generate_contract(int number_to_generate, Service &service);

        /**
         * Returneaza lista de discipline din contract.
         * @return Referinta la vectorul de discipline.
         */
        std::vector<Disciplina>& get_lista_discipline_contract();

        /**
         * Exporta contractul intr-un fisier.
         * @param file_name Numele fisierului in care se exporta.
         */
        void export_contract(std::string& file_name) const;
};