#pragma once
#include <string>
#include <utility>

class Apartament {
private:
    int id;
    std::string suprafata;
    std::string strada;
    int pret;

public:
    /*
     *  Constructor default
     */
    Apartament(const int id, std::string suprafata, std::string strada, const int pret):id(id),suprafata(std::move(suprafata)),strada(std::move(strada)),pret(pret){}

    /*
     *  Constructor de copiere
     */
    Apartament(const Apartament &other);

    /*
     *  Id getter
     */
    int get_id() const { return id;}

    /*
     *  Suprafata getter
     */
    std::string get_suprafata() const { return suprafata;}

    /*
     *  Strada getter
     */
    std::string get_strada() const { return strada;}

    /*
     *  Pret getter
     */
    int get_pret() const { return pret;}

    /*
     *  Suprascriere operator ==
     */
    bool operator==(const Apartament &other) const;
};
