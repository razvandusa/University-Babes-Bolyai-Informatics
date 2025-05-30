#pragma once
#include "repository.h"

class Service {
private:
    Repository &repository;

public:
    /*
     *  Constructor default
     */
    Service(Repository &repository) : repository(repository) {}

    /*
     *  Functia valideaza datele de intrare din fisier, iar daca sunt valide le incarca in lista
     */
    void load_from_file_service();

    /*
     *  Functia scrie in fisier apartamentele din lista de apartamente
     */
    void write_to_file_service();

    /*
     *  Functia sterge apartamentul din lista
     */
    void delete_apartament_service(int id);

    /*
     *  Functia filtreaza dupa un interval suprafetele apartamentelor
     */
    std::vector<Apartament> filtreaza_suprafata(const std::string& min, const std::string& max) const;

    /*
     *  Functia filtreaza dupa un interval pretul apartamentelor
     */
    std::vector<Apartament> filtreaza_pret(const std::string& min, const std::string& max) const;

    /*
     *  Functia returneaza lista cu apartamente
     */
    std::vector<Apartament>& get_all() const;
};
