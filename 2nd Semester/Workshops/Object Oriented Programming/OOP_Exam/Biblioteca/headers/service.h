#pragma once
#include "repository.h"

class Service {
    public:
        /*
         *  Creeaza un service cu un repo
         *  repository : Repository
         */
        Service(Repository &repository) : repository(repository) {}

        /*
         *  Incarca datele din fisier
         *  return : None
         */
        void load_from_file() {
            repository.load_from_file();
        }

        /*
         * Scrie datele in fisier
         * return : None
         */
        void write_to_file() {
            repository.write_to_file();
        }

        /*
         *  Criteriul de comparare compara doua carti dupa titlu
         *  return 1 : daca sunt in ordine lexicografica
         *  return 0 : altfel
         */
        static bool comparare_criteriu_sortare(Carte& c1, Carte& c2) {
            return c1.get_titlu() < c2.get_titlu();
        }

        /*
         *  Sorteaza cartile dupa titlu
         *  return : None
         */
        void sortare_titlu();

        /*
         *  Filtreaza cartile dupa gen si returneaza lista de carti filtrata
         *  return : std::vector<Carte>
         */
        std::vector<Carte> filtrare_gen(const std::string& gen_cautat);

        /*
         *  Returneaza lista de carti
         *  return : std::vector<Carte>
         */
        std::vector<Carte>& get_all() {
            return repository.get_all();
        }

    private:
        Repository& repository;
};
