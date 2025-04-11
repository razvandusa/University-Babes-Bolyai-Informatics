#include "../headers/domain.h"
#include <iostream>
/*
*  Constructor implicit
*/
Disciplina::Disciplina(): id(0), denumire(""), ore(0), tip(""), cadru_didactic("") {}

/*
*  Constructor
*/
Disciplina::Disciplina(int id, const std::string &denumire, int ore, const std::string &tip, const std::string &cadru_didactic) {
        this->id = id;
        this->denumire = denumire;
        this->ore = ore;
        this->tip = tip;
        this->cadru_didactic = cadru_didactic;
}

/*
 *  Constructor de copiere
 */
Disciplina::Disciplina(const Disciplina &other) : id(other.get_id()),denumire(other.get_denumire()),ore(other.get_ore()),tip(other.get_tip()),cadru_didactic(other.get_cadru_didactic()){
        std::cout << "\nS-a realizat o copiere!\n";
}


/*
* Returneaza id-ul disciplinei
*/
int Disciplina::get_id() const{
        return id;
}

/*
 *  Seteaza valoarea campului id
 *  new_id : noua valoarea a campului id
 */
void Disciplina::set_id(const int new_id) {
        id = new_id;
}

/*
 * Returneaza denumirea disciplinei
 */
std::string Disciplina::get_denumire() const {
        return denumire;
}

/*
 *  Seteaza valoarea campului denumire
 *  new_denumire : noua valoare a campului denumire
 */
void Disciplina::set_denumire(const std::string &new_denumire) {
        denumire = new_denumire;
}

/*
 * Returneaza numarul de ore a disciplinei
 */
int Disciplina::get_ore() const {
        return ore;
}

/*
 *  Seteaza valoarea campului ore
 *  new_ore : noua valoarea a campului ore
 */
void Disciplina::set_ore(int new_ore) {
        ore = new_ore;
}

/*
 * Returneaza tipul disciplinei
 */
std::string Disciplina::get_tip() const {
        return tip;
}

/*
 *  Seteaza valoarea campului tip
 *  new_tip : noua valoare a campului tip
 */
void Disciplina::set_tip(const std::string &new_tip) {
        tip = new_tip;
}

/*
 * Returneaza cadrul didactic al disciplinei
 */
std::string Disciplina::get_cadru_didactic() const {
        return cadru_didactic;
}

/*
 *  Seteaza valoarea campului cadru_didactic
 *  new_cadru_didactic : noua valoarea a campului cadru didactic
 */
void Disciplina::set_cadru_didactic(const std::string &new_cadru_didactic) {
        cadru_didactic = new_cadru_didactic;
}