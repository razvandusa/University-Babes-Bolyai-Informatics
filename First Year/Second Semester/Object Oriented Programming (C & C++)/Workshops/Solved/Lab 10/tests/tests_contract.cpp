#include "../headers/contract.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <ostream>

void test_clear_contract() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    Contract contract;

    service.add_disciplina(1,"Matematica",4,"Obligatorie","Maria Antonescu");
    assert(contract.get_lista_discipline_contract().empty());
    contract.add_disciplina_contract(1,service);
    contract.clear_contract();
    assert(contract.get_lista_discipline_contract().empty());
}

void test_add_contract() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    Contract contract;

    service.add_disciplina(1,"Matematica",4,"Obligatorie","Maria Antonescu");
    service.add_disciplina(2,"Limba Romana",8,"Optionala","Ioan Paul");

    assert(contract.get_lista_discipline_contract().empty() == true);
    contract.add_disciplina_contract(1,service);
    contract.add_disciplina_contract(2,service);
    assert(contract.get_lista_discipline_contract().size() == 2);
}

void test_generate_contract() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    Contract contract;

    try {
        contract.generate_contract(2, service);
        assert(false);
    } catch (...) {
        assert(true);
    }

    service.add_disciplina(1,"Matematica",4,"Obligatorie","Maria Antonescu");
    service.add_disciplina(2,"Limba Romana",8,"Optionala","Ioan Paul");
    service.add_disciplina(3,"Religie",12,"Optionala","Lorand Gabos");

    contract.generate_contract(2, service);
    assert(contract.get_lista_discipline_contract().size() == 2);

    try {
        contract.generate_contract(10, service);
        assert(false);
    } catch (...) {
        assert(true);
    }
}

void test_export_contract() {
    std::unique_ptr<RepositoryMemory> repository = std::make_unique<RepositoryMemory>();
    Service service(std::move(repository));
    Contract contract;

    service.add_disciplina(1,"Matematica",4,"Obligatorie","Maria Antonescu");
    contract.add_disciplina_contract(1,service);

    std::ifstream fin ("/Users/razvandusa/CLionProjects/Lab 8/tests/tests_contract_export.html");
    std::ofstream fout ("/Users/razvandusa/CLionProjects/Lab 8/tests/tests_contract_export.html");
    try {
        contract.export_contract("/Users/razvandusa/CLionProjects/Lab 8/tests/tests_contract_export");
        assert(false);
    } catch (...) {
        assert(true);
    }
    contract.export_contract("/Users/razvandusa/CLionProjects/Lab 8/tests/tests_contract_export.html");

    int id;
    fin >> id;
    //assert(id == 1);
    fin.close();
}

void teste_contract() {
    test_add_contract();
    test_clear_contract();
    test_generate_contract();
    test_export_contract();
}