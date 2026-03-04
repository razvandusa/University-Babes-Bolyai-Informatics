#include "../headers/domain.h"
#include <iostream>

Disciplina::Disciplina(): id(0), denumire(""), ore(0), tip(""), cadru_didactic("") {}

Disciplina::Disciplina(int id, const std::string &denumire, int ore, const std::string &tip, const std::string &cadru_didactic) {
        this->id = id;
        this->denumire = denumire;
        this->ore = ore;
        this->tip = tip;
        this->cadru_didactic = cadru_didactic;
}

Disciplina::Disciplina(const Disciplina &other) : id(other.get_id()),denumire(other.get_denumire()),ore(other.get_ore()),tip(other.get_tip()),cadru_didactic(other.get_cadru_didactic()){
        std::cout << "\nS-a realizat o copiere!\n";
}

int Disciplina::get_id() const{
        return id;
}

void Disciplina::set_id(const int new_id) {
        id = new_id;
}

std::string Disciplina::get_denumire() const {
        return denumire;
}

void Disciplina::set_denumire(const std::string &new_denumire) {
        denumire = new_denumire;
}

int Disciplina::get_ore() const {
        return ore;
}

void Disciplina::set_ore(int new_ore) {
        ore = new_ore;
}

std::string Disciplina::get_tip() const {
        return tip;
}

void Disciplina::set_tip(const std::string &new_tip) {
        tip = new_tip;
}

std::string Disciplina::get_cadru_didactic() const {
        return cadru_didactic;
}

void Disciplina::set_cadru_didactic(const std::string &new_cadru_didactic) {
        cadru_didactic = new_cadru_didactic;
}

bool Disciplina::operator==(const Disciplina& other) const {
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