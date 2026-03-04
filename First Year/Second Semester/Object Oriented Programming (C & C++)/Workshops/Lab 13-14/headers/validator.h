#pragma once
#include <string>

class Validator {
public:
    /**
     * Verifica daca id-ul este valid.
     */
    static bool id_valid(int id);

    /**
     * Verifica daca denumirea este valida.
     */
    static bool denumire_valida(const std::string& denumire);

    /**
     * Verifica daca numarul de ore este valid.
     */
    static bool ore_valide(int ore);

    /**
     * Verifica daca tipul este valid.
     */
    static bool tip_valid(const std::string& tip);

    /**
     * Verifica daca se poate converti un string intr-un int.
     * @param intreg Stringul de verificat.
     * @return Valoarea convertita daca este valida.
     */
    static int conversie_valida(const std::string& intreg);
};
