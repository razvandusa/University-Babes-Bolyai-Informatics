#include "../headers/repository.h"
#include "../headers/validator.h"
#include <fstream>
#include <iostream>
Disciplina disciplina_vida;

Repository::Repository() {
    lista_discipline = std::vector<Disciplina> {};
    lista_discipline.reserve(100);
}

std::vector<Disciplina>& Repository::get_lista_discipline() {
    return lista_discipline;
}

void Repository::add_disciplina(const Disciplina& disciplina) {
    lista_discipline.push_back(disciplina);
}

bool Repository::exista_disciplina(int id) const {
    for (const auto &disciplina : lista_discipline) {
        if (disciplina.get_id() == id) {
            return true;
        }
    }
    return false;
}

Disciplina& Repository::get_disciplina(int id) {
    for (auto &disciplina : lista_discipline) {
        if (disciplina.get_id() == id) {
            return disciplina;
        }
    }
    return disciplina_vida;
}

void Repository::remove_disciplina(int id) {
    for (auto disciplina = lista_discipline.begin(); disciplina < lista_discipline.end(); ++disciplina) {
        if (disciplina->get_id() == id) {
            lista_discipline.erase(disciplina);
        }
    }
}

void Repository::update_disciplina(int id, const Disciplina& updated_disciplina) {
    Disciplina& disciplina = get_disciplina(id);
    disciplina = updated_disciplina;
}

void RepositoryFile::add_disciplina(const Disciplina &disciplina) {
    Repository::add_disciplina(disciplina);
    writeToFile();
}

void RepositoryFile::remove_disciplina(int id) {
    Repository::remove_disciplina(id);
    writeToFile();
}

void RepositoryFile::loadFromFile() {
    std::ifstream fin(filename);
    int id, ore;
    std::string denumire, tip, cadru_didactic;
    while (fin >> id >> std::ws && std::getline(fin, denumire)
               && fin >> ore >> std::ws && std::getline(fin, tip)
               && std::getline(fin, cadru_didactic)) {
        Disciplina disciplina(id, denumire, ore, tip, cadru_didactic);
        Repository::add_disciplina(disciplina);
    }
    fin.close();
}

void RepositoryFile::writeToFile() {
    std::ofstream fout(filename);
    for (const auto &disciplina : Repository::get_lista_discipline()) {
        fout << disciplina.get_id() << std::endl;
        fout << disciplina.get_denumire() << std::endl;
        fout << disciplina.get_ore() << std::endl;
        fout << disciplina.get_tip() << std::endl;
        fout << disciplina.get_cadru_didactic() << std::endl;
    }
    fout.close();
}

