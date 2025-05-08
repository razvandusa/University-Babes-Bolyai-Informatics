#include <iostream>
#include <QApplication>
#include "headers/disciplineGUI.h"
#include "headers/ui.h"
#include "tests/tests_contract.h"
#include "tests/tests_domain.h"
#include "tests/tests_exceptions.h"
#include "tests/tests_repository.h"
#include "tests/tests_validator.h"
#include "tests/tests_service.h"
#include "tests/tests_undo.h"
using namespace std;

void teste () {
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
}

int main (int argc, char *argv[]) {
    teste();

    std::unique_ptr<RepositoryMemory> repository;
    std::unique_ptr<RepositoryProbability> repositoryProbability = std::make_unique<RepositoryProbability>();
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
                repository = std::make_unique<RepositoryMemory>();
                choosing = false;
            } else if (optiune == 2) {
                repository = std::make_unique<RepositoryFile>("/Users/razvandusa/CLionProjects/Lab 10/file.txt");
                choosing = false;
            } else {
                std::cout << "Optiune invalida!\n";
            }
        } catch (...) {
            std::cout << "Optiune invalida!\n";
        }
    }

    Service service(std::move(repository));
    choosing = true;
    while (choosing) {
        try {
            std::cout << "\nAlege tipul de interfata :\n";
            std::cout << "1. Interfata consola\n";
            std::cout << "2. Interfata grafica\n";
            std::getline(std::cin, input);
            int optiune = stoi(input);
            if (optiune == 1) {
                UI ui(service);
                ui.run();
                choosing = false;
            }
            if (optiune == 2) {
                QApplication a(argc, argv);
                DisciplineGUI window(service);
                window.show();
                return a.exec();
            }
            std::cout << "Optiune invalida!\n";
        } catch (...) {
            std::cout << "Optiune invalida!\n";
        }
    }
}
