#include "../headers/repository.h"
#include <cassert>
#include <fstream>
#include <iostream>

void test_constructor_repository_implicit() {
    RepositoryMemory repository;
    assert(repository.get_lista_discipline().empty());
}

void test_add_disciplina() {
    RepositoryMemory repository;
    repository.add_disciplina(Disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul"));
    assert(repository.get_lista_discipline().size() == 1);
}

void test_exista_disciplina() {
    RepositoryMemory repository;
    repository.add_disciplina(Disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul"));
    assert(repository.exista_disciplina(2) == true);
    assert(repository.exista_disciplina(4) == false);
}

void test_get_disciplina() {
    RepositoryMemory repository;
    Disciplina disciplina = Disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul");
    repository.add_disciplina(disciplina);
    assert(repository.get_disciplina(2) == disciplina);
    assert(repository.get_disciplina(1) == Disciplina());
}

void test_remove_disciplina() {
    RepositoryMemory repository;
    repository.add_disciplina(Disciplina(1,"Limba Romana",4,"Obligatorie","Andrei Maruta"));
    repository.add_disciplina(Disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul"));
    repository.remove_disciplina(2);
    assert(repository.get_lista_discipline().size() == 1);
    assert(repository.exista_disciplina(1) == true);
    assert(repository.exista_disciplina(2) == false);
}

void test_update_disciplina() {
    RepositoryMemory repository;
    repository.add_disciplina(Disciplina(1,"Limba Romana",4,"Obligatorie","Andrei Maruta"));
    repository.update_disciplina(1,Disciplina(1,"Matematica",4,"Obligatorie","Ioan Paul"));
    assert(repository.get_disciplina(1) == Disciplina(1,"Matematica",4,"Obligatorie","Ioan Paul"));
}

void test_write_to_file() {
    std::string file_name = "/Users/razvandusa/CLionProjects/Lab 10/tests/tests_file.txt";
    std::ofstream fout(file_name, std::ofstream::trunc);
    fout.close();

    RepositoryFile repository(file_name);
    repository.add_disciplina(Disciplina(1,"Limba Romana",4,"Obligatorie","Andrei Maruta"));

    std::ifstream fin(file_name);
    if (!fin.is_open()) {
        std::cerr << "Nu s-a putut deschide fisierul pentru citire.\n";
        assert(false);
    }
    std::string line1, line2, line3, line4, line5;
    std::getline(fin, line1);
    std::getline(fin, line2);
    std::getline(fin, line3);
    std::getline(fin, line4);
    std::getline(fin, line5);
    fin.close();

    assert(line1 == "1");
    assert(line2 == "Limba Romana");
    assert(line3 == "4");
    assert(line4 == "Obligatorie");
    assert(line5 == "Andrei Maruta");
}

void test_load_from_file() {
    std::string file_name = "/Users/razvandusa/CLionProjects/Lab 10/tests/tests_file.txt";
    std::ofstream fout(file_name, std::ofstream::trunc);

    fout << "1\nLimba Romana\n4\nObligatorie\nAndrei Maruta\n";
    fout << "2\nMatematica\n4\nObligatorie\nIoan_Paul\n";
    fout.close();

    RepositoryFile repository(file_name);
    const auto& lista_discipline = repository.get_lista_discipline();
    assert(lista_discipline.size() == 2);
    assert(lista_discipline[0] == Disciplina(1, "Limba Romana", 4, "Obligatorie", "Andrei Maruta"));
    assert(lista_discipline[1] == Disciplina(2, "Matematica", 4, "Obligatorie", "Ioan_Paul"));
    repository.remove_disciplina(1);
    assert(lista_discipline.size() == 1);
    assert(lista_discipline[0] == Disciplina(2, "Matematica", 4, "Obligatorie", "Ioan_Paul"));
}

void teste_repository() {
    test_constructor_repository_implicit();
    test_add_disciplina();
    test_exista_disciplina();
    test_get_disciplina();
    test_remove_disciplina();
    test_update_disciplina();
    test_write_to_file();
    test_load_from_file();
}