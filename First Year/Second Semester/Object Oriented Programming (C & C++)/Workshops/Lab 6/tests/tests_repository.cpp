#include "../headers/repository.h"
#include <cassert>

void test_constructor_repository_implicit() {
    Repository repository;
    assert(repository.get_lista_discipline().size() == 0);
}

void test_add_disciplina() {
    Repository repository;
    repository.add_disciplina(Disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul"));
    assert(repository.get_lista_discipline().size() == 1);
}

void test_exista_disciplina() {
    Repository repository;
    repository.add_disciplina(Disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul"));
    assert(repository.exista_disciplina(2) == true);
    assert(repository.exista_disciplina(4) == false);
}

void test_get_disciplina() {
    Repository repository;
    Disciplina disciplina = Disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul");
    repository.add_disciplina(disciplina);
    assert(repository.get_disciplina(2) == disciplina);
}

void test_remove_disciplina() {
    Repository repository;
    repository.add_disciplina(Disciplina(1,"Limba Romana",4,"Obligatorie","Andrei Maruta"));
    repository.add_disciplina(Disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul"));
    repository.remove_disciplina(2);
    assert(repository.get_lista_discipline().size() == 1);
    assert(repository.exista_disciplina(1) == true);
    assert(repository.exista_disciplina(2) == false);
}

void test_update_disciplina() {
    Repository repository;
    repository.add_disciplina(Disciplina(1,"Limba Romana",4,"Obligatorie","Andrei Maruta"));
    repository.update_disciplina(1,Disciplina(1,"Matematica",4,"Obligatorie","Ioan Paul"));
    assert(repository.get_disciplina(1) == Disciplina(1,"Matematica",4,"Obligatorie","Ioan Paul"));
}

void teste_repository() {
    test_constructor_repository_implicit();
    test_add_disciplina();
    test_exista_disciplina();
    test_get_disciplina();
    test_remove_disciplina();
    test_update_disciplina();
}