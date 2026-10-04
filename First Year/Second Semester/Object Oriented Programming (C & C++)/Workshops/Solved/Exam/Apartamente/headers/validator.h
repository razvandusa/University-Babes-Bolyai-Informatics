#pragma once
#include <string>
#include <vector>

class Apartament;

class Validator {
public:
    /*
     *  Validator pentru id
     */
    static bool id_valid(const std::string& id, std::vector<Apartament>& lista_apartamente);

    /*
     *  Validator pentru suprafata
     */
    static bool suprafata_valida(const std::string& suprafata);

    /*
     *  Validator pentru strada
     */
    static bool strada_valida(const std::string& strada);

    /*
     *  Validator pentru pret
     */
    static bool pret_valid(const std::string& pret);
};
