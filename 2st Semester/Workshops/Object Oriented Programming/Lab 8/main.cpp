#include <iostream>
#include "headers/ui.h"
#include "tests/tests_contract.h"
#include "tests/tests_domain.h"
#include "tests/tests_exceptions.h"
#include "tests/tests_repository.h"
#include "tests/tests_validator.h"
#include "tests/tests_service.h"
#include "tests/tests_undo.h"
using namespace std;

int main () {
    teste_contract();
    std::cout << "Testele contract au trecut cu succes!\n";
    teste_domain();
    std::cout << "Testele domain au trecut cu succes!\n";
    teste_exceptions();
    std::cout << "Testele exceptions au trecut cu succes!\n";
    teste_repository();
    std::cout << "Testele repository au trecut cu succes!\n";
    teste_validator();
    std::cout << "Testele validator au trecut cu succes!\n";
    teste_service();
    std::cout << "Testele service au trecut cu succes!\n";
    teste_undo();
    std::cout << "Testele undo au trecut cu succes!\n";

    std::unique_ptr<Repository> repository;
    std::string input;
    bool choosing = true;
    while (choosing) {
        try {
            std::cout << "\nAlege tipul de repository :\n";
            std::cout << "1. Repository in memorie\n";
            std::cout << "2. Repository din fisier\n";
            std::getline(std::cin, input);
            int optiune = stoi(input);
            if (optiune == 1) {
                repository = std::make_unique<Repository>();
                choosing = false;
            } else if (optiune == 2) {
                repository = std::make_unique<RepositoryFile>("/Users/razvandusa/CLionProjects/Lab 8/file.txt");
                choosing = false;
            } else {
                std::cout << "Optiune invalida!\n";
            }
        } catch (...) {
            std::cout << "Optiune invalida!\n";
        }
    }

    Service service(std::move(repository));
    UI ui(service);
    ui.run();
}


