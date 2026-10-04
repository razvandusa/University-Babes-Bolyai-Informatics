#include <iostream>
#include "headers/ui.h"
#include "tests/tests_domain.h"
#include "tests/tests_repository.h"
#include "tests/tests_validator.h"
#include "tests/tests_service.h"
using namespace std;

int main () {
    teste_domain();
    std::cout << "Testele domain au trecut cu succes!\n";
    teste_repository();
    std::cout << "Testele repository au trecut cu succes!\n";
    teste_validator();
    std::cout << "Testele validator au trecut cu succes!\n";
    teste_service();
    std::cout << "Testele service au trecut cu succes!\n";

    UI ui;
    ui.run();
}


