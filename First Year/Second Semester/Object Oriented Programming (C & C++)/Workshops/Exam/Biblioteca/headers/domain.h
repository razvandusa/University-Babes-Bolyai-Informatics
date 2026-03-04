#pragma once
#include <string>
#include <utility>

class Carte {
public:
    /*
     *  Functia creeaza o carte cu valorile citite
     *  id : int
     *  cod : int
     *  titlu : std::string
     *  autor : std::string
     *  gen : std::string
     */
    Carte(int id, int cod, std::string titlu, std::string autor, std::string gen) : id(id), cod(cod), titlu(std::move(titlu)), autor(std::move(autor)), gen(std::move(gen)) {}

    /*
     *  Returneaza id
     *  return : int
     */
    int get_id() {
        return id;
    }

    /*
     *  Returneaza cod
     *  return : int
     */
    int get_cod() {
        return cod;
    }

    /*
     *  Returneaza titlu
     *  return : std::string
     */
    std::string get_titlu() {
        return titlu;
    }

    /*
     *  Returneaza autor
     *  return : std::string
     */
    std::string get_autor() {
        return autor;
    }

    /*
     *  Returneaza gen
     *  return : std::string
     */
    std::string get_gen() {
        return gen;
    }

private:
    int id;
    int cod;
    std::string titlu;
    std::string autor;
    std::string gen;
};
