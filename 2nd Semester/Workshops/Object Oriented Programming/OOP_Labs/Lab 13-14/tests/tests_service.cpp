#include "../headers/service.h"
#include <cassert>
#include <iostream>
#include <ostream>

void test_add_disciplina_service() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    assert(service.add_disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul") == "Operatie efectuata cu succes!");
    try {
        service.add_disciplina(-20,"Matematica",4,"Obligatorie","Ioan Paul");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        service.add_disciplina(2,"Random",4,"Obligatorie","Ioan Paul");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        service.add_disciplina(2,"Matematica",1000,"Obligatorie","Ioan Paul");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        service.add_disciplina(2,"Matematica",4,"Random","Ioan Paul");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        service.add_disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul");
        assert(false);
    } catch (...) {
        assert(true);
    }
}

void test_remove_disciplina_service() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    service.add_disciplina(1,"Limba Romana",8,"Optionala","Maria Antonescu");
    service.add_disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul");
    assert(service.remove_disciplina(1) == "Operatie efectuata cu succes!");
    try {
        service.remove_disciplina(1);
        assert(false);
    } catch (...) {
        assert(true);
    }
}

void test_update_disciplina_service() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    service.add_disciplina(1,"Limba Romana",8,"Optionala","Maria Antonescu");
    assert(service.update_disciplina(1,"Matematica",4,"Obligatorie","Ioan Paul") == "Operatie efectuata cu succes!");
    try {
        service.update_disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        service.update_disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        service.update_disciplina(1,"Random",4,"Obligatorie","Ioan Paul");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        service.update_disciplina(1,"Matematica",1000,"Obligatorie","Ioan Paul");
        assert(false);
    } catch (...) {
        assert(true);
    }
    try {
        service.update_disciplina(1,"Matematica",4,"Random","Ioan Paul");
        assert(false);
    } catch (...) {
        assert(true);
    }
}

void test_find_disciplina_service() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    service.add_disciplina(1,"Limba Romana",8,"Optionala","Maria Antonescu");
    assert(service.find_disciplina(1) == Disciplina(1,"Limba Romana",8,"Optionala","Maria Antonescu"));
    try {
        service.find_disciplina(0);
        assert(false);
    } catch (...) {
        assert(true);
    }
}

void test_get_lista_discipline_service() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    assert(service.get_lista_discipline().empty() == true);
    service.add_disciplina(1,"Limba Romana",8,"Optionala","Maria Antonescu");
    service.add_disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul");
    assert(service.get_lista_discipline().size() == 2);
}

void test_filtrare_discipline_service() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    service.add_disciplina(1,"Limba Romana",8,"Optionala","Maria Antonescu");
    service.add_disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul");
    service.add_disciplina(3,"Religie",12,"Optionala","Lorand Gabos");

    std::vector<Disciplina> lista_discipline_filtrata = service.filtrare_discipline(
        service.get_lista_discipline(), "numar ore", "10");
    assert(lista_discipline_filtrata[0] == Disciplina(3,"Religie",12,"Optionala","Lorand Gabos"));

    lista_discipline_filtrata = service.filtrare_discipline(service.get_lista_discipline(), "cadru didactic", "Ioan Paul");
    assert(lista_discipline_filtrata[0] == Disciplina(2,"Matematica",4,"Obligatorie","Ioan Paul"));
}

void test_sortare_discipline_service() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    service.add_disciplina(1,"Matematica",4,"Obligatorie","Maria Antonescu");
    service.add_disciplina(2,"Limba Romana",8,"Optionala","Ioan Paul");
    service.add_disciplina(3,"Religie",12,"Optionala","Lorand Gabos");
    std::vector<Disciplina> lista_discipline = service.get_lista_discipline();

    service.sortare_discipline(lista_discipline, "denumire");
    assert(lista_discipline[0] == Disciplina(2,"Limba Romana",8,"Optionala","Ioan Paul"));
    assert(lista_discipline[1] == Disciplina(1,"Matematica",4,"Obligatorie","Maria Antonescu"));
    assert(lista_discipline[2] == Disciplina (3,"Religie",12,"Optionala","Lorand Gabos"));

    service.sortare_discipline(lista_discipline, "numar ore");
    assert(lista_discipline[0] == Disciplina(1,"Matematica",4,"Obligatorie","Maria Antonescu"));
    assert(lista_discipline[1] == Disciplina(2,"Limba Romana",8,"Optionala","Ioan Paul"));
    assert(lista_discipline[2] == Disciplina (3,"Religie",12,"Optionala","Lorand Gabos"));

    service.sortare_discipline(lista_discipline, "cadru didactic");
    assert(lista_discipline[0] == Disciplina(2,"Limba Romana",8,"Optionala","Ioan Paul"));
    assert(lista_discipline[1] == Disciplina (3,"Religie",12,"Optionala","Lorand Gabos"));
    assert(lista_discipline[2] == Disciplina(1,"Matematica",4,"Obligatorie","Maria Antonescu"));

    service.sortare_discipline(lista_discipline, "tip");
    assert(lista_discipline[0] == Disciplina(1,"Matematica",4,"Obligatorie","Maria Antonescu"));
    assert(lista_discipline[1] == Disciplina(2,"Limba Romana",8,"Optionala","Ioan Paul"));
    assert(lista_discipline[2] == Disciplina (3,"Religie",12,"Optionala","Lorand Gabos"));
}

void test_raport_discipline_service() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));

    service.add_disciplina(1, "Matematica", 5, "Obligatorie", "Popescu");
    service.add_disciplina(2, "Limba Romana", 4, "Obligatorie", "Ionescu");
    service.add_disciplina(3, "Religie", 2, "Optionala", "Marin");
    service.add_disciplina(4, "Religie", 3, "Optionala", "Marin");
    service.add_disciplina(5, "Religie", 2, "Facultativa", "Dumitrescu");

    std::vector<Disciplina>& lista = service.get_lista_discipline();
    auto raport = Service::raport_discipline(lista);

    assert(raport.size() == 3); //
    assert(raport["Obligatorie"].get_aparitii() == 2);
    assert(raport["Optionala"].get_aparitii() == 2);
    assert(raport["Facultativa"].get_aparitii() == 1);
}

void teste_service() {
    test_add_disciplina_service();
    test_remove_disciplina_service();
    test_update_disciplina_service();
    test_find_disciplina_service();
    test_get_lista_discipline_service();
    test_filtrare_discipline_service();
    test_sortare_discipline_service();
    test_raport_discipline_service();
}