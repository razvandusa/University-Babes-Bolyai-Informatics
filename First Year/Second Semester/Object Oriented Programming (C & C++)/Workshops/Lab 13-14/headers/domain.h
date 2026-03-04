#pragma once
#include <string>

class Disciplina {
public:
    /**
     * Constructor implicit
     */
    Disciplina();

    /**
     * Constructor
     */
    Disciplina(int id, const std::string &denumire, int ore, const std::string &tip, const std::string &cadru_didactic);

    /**
     * Constructor de copiere
     */
    Disciplina(const Disciplina& other);

    /**
     * Returneaza id-ul disciplinei
     */
    int get_id() const;

    /**
     * Seteaza valoarea campului id
     * @param new_id Noua valoare a campului id
     */
    void set_id(int new_id);

    /**
     * Returneaza denumirea disciplinei
     */
    std::string get_denumire() const;

    /**
     * Seteaza valoarea campului denumire
     * @param new_denumire Noua valoare a campului denumire
     */
    void set_denumire(const std::string &new_denumire);

    /**
     * Returneaza numarul de ore a disciplinei
     */
    int get_ore() const;

    /**
     * Seteaza valoarea campului ore
     * @param new_ore Noua valoare a campului ore
     */
    void set_ore(int new_ore);

    /**
     * Returneaza tipul disciplinei
     */
    std::string get_tip() const;

    /**
     * Seteaza valoarea campului tip
     * @param new_tip Noua valoare a campului tip
     */
    void set_tip(const std::string &new_tip);

    /**
     * Returneaza cadrul didactic al disciplinei
     */
    std::string get_cadru_didactic() const;

    /**
     * Seteaza valoarea campului cadru_didactic
     * @param new_cadru_didactic Noua valoare a campului cadru didactic
     */
    void set_cadru_didactic(const std::string &new_cadru_didactic);

    /**
     * Supraincarcarea operatorului ==
     */
    bool operator==(const Disciplina& other) const;

private:
    int id;
    std::string denumire;
    int ore;
    std::string tip;
    std::string cadru_didactic;
};