#pragma once
#include <string>

class Validator {
public:
    /*
     *  Verifica daca id-ul este valid
     */
    bool id_valid(int id);

    /*
     *  Verifica daca denumirea este valida
     */
    bool denumire_valida(const std::string& denumire);

    /*
     *  Verifica daca orele sunt valide
     */
    bool ore_valide(int ore);

    /*
     *  Verifica daca tipul este valid
     */
    bool tip_valid(const std::string& tip);
};
