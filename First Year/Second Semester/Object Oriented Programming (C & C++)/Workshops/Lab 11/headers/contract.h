#pragma once
#include "service.h"

class Contract {
    private:
        std::vector<Disciplina> contract;

    public:
        /*
         *  Constructor implicit
         */
        Contract();

        /*
         *  Se goleste contractul
         */
        void clear_contract();

        /*
         *  Se adauga o disciplina in contract
         *  id : id-ul disciplinei pe care o adaugam
         *  service : containerul de unde se vor adauga disciplinele
         */
        void add_disciplina_contract(int id, Service &service);

        /*
         *  Genereaza un contract
         *  number_to_generate : numarul de discipline care sa fie generate
         *  service : containerul de unde se vor lua disciplinele
         */
        void generate_contract(int number_to_generate, Service &service);

        /*
         *  Returneaza lista de discipline
         */
        std::vector<Disciplina>& get_lista_discipline_contract();

        /*
         *  Exporta contractul intr-un fisier
         *  file_name : numele fisierului
         */
        void export_contract(std::string& file_name) const;
};