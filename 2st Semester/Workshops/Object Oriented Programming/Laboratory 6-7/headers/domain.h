#pragma once
#include <string>

class Disciplina {
public:
    /*
     *  Constructor implicit
     */
    Disciplina();

    /*
     *  Constructor
     */
    Disciplina(int id, const std::string &denumire, int ore, const std::string &tip, const std::string &cadru_didactic);

    /*
     *  Returneaza id-ul disciplinei
     */
    int get_id() const;

    /*
     *  Seteaza valoarea campului id
     *  new_id : noua valoarea a campului id
     */
    void set_id(int new_id);

    /*
     *  Returneaza denumirea disciplinei
     */
    std::string get_denumire() const;

    /*
     *  Seteaza valoarea campului denumire
     *  new_denumire : noua valoare a campului denumire
     */
    void set_denumire(const std::string &new_denumire);

    /*
     *  Returneaza numarul de ore a disciplinei
     */
    int get_ore() const;

    /*
     *  Seteaza valoarea campului ore
     *  new_ore : noua valoarea a campului ore
     */
    void set_ore(int new_ore);

    /*
     *  Returneaza tipul disciplinei
     */
    std::string get_tip() const;

    /*
     *  Seteaza valoarea campului tip
     *  new_tip : noua valoare a campului tip
     */
    void set_tip(const std::string &new_tip);

    /*
     *  Returneaza cadrul didactic al disciplinei
     */
    std::string get_cadru_didactic() const;

    /*
     *  Seteaza valoarea campului cadru_didactic
     *  new_cadru_didactic : noua valoarea a campului cadru didactic
     */
    void set_cadru_didactic(const std::string &new_cadru_didactic);

    /*
     *  Supraincarcarea operatorului ==
     */
    bool operator==(const Disciplina& other) const {
        if (id != other.id) {
            return false;
        }
        if (ore != other.ore) {
            return false;
        }
        if (tip != other.tip) {
            return false;
        }
        if (denumire != other.denumire) {
            return false;
        }
        if (cadru_didactic != other.cadru_didactic) {
            return false;
        }
        return true;
    }

private:
    int id;
    std::string denumire;
    int ore;
    std::string tip;
    std::string cadru_didactic;
};