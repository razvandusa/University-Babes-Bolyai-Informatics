#include "tests_undo.h"
#include "../headers/repository.h"
#include "../headers/service.h"
#include <cassert>

void test_undo_adauga() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));

    try {
        service.undo();
        assert(false);
    } catch (...) {
        assert(true);
    }

    service.add_disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul");
    assert(service.get_lista_discipline().size() == 1);

    service.undo();
    assert(service.get_lista_discipline().empty());
}

void test_undo_sterge() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));

    service.add_disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul");
    assert(service.get_lista_discipline().size() == 1);
    service.remove_disciplina(2);
    assert(service.get_lista_discipline().empty());

    service.undo();
    assert(service.get_lista_discipline().size() == 1);
}

void test_undo_update() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    service.add_disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul");
    assert(service.find_disciplina(2) == Disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul"));

    service.update_disciplina(2,"Limba Romana",8,"Optionala","Maria Antonescu");
    assert(service.find_disciplina(2) == Disciplina(2,"Limba Romana",8,"Optionala","Maria Antonescu"));

    service.undo();
    assert(service.find_disciplina(2) == Disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul"));
}

void teste_undo() {
    test_undo_adauga();
    test_undo_sterge();
    test_undo_update();
}