#pragma once
#include <string>

class Validator {
public:
    /*
     *  Verifica daca id-ul este valid
     */
    static bool id_valid(int id);

    /*
     *  Verifica daca denumirea este valida
     */
    static bool denumire_valida(const std::string& denumire);

    /*
     *  Verifica daca orele sunt valide
     */
    static bool ore_valide(int ore);

    /*
     *  Verifica daca tipul este valid
     */
    static bool tip_valid(const std::string& tip);

    /*
     *  Verifica daca se poate converti din string in int
     */
    static int conversie_valida(const std::string& intreg);
};
