#pragma once
#include <vector>
#include "domain.h"

class Repository {
    private:
    std::string filename;
    std::vector<Apartament> lista_apartamente;

    public:
    /*
     *  Constructor default
     */
    Repository(std::string filename):filename(std::move(filename)){}

    /*
     *  Functia incarca din fisier apartamentele in lista de apartamente
     */
    void load_from_file();

    /*
     *  Functia scrie in fisier apartamentele din lista de apartamente
     */
    void write_to_file();

    /*
     *  Functia sterge un apartament din lista dupa id
     */
    void delete_apartament(int id);

    /*
     *  Functia returneaza numele filename-ului
     */
    std::string& get_filename();

    /*
     *  Functia returneaza lista cu apartamente
     */
    std::vector<Apartament>& get_all();
};
